<?php

namespace WellCat\Controllers;

use Silex\Application;
use PDO;
use Symfony\Component\HttpFoundation\Request;
use WellCat\JsonResponse;
use WellCat\Validators\PetRequestValidator;

class PetController
{
    protected $app;

    public function __construct(\Silex\Application $app)
    {
        $this->app = $app;
        $this->app['session']->start();
    }

    /**
     * Function is given some required information to create a new pet in the system
     * @param Request $request holds JSON data of pet infromation needed to create a pet
     *       =>[text] name holds the pets name
     *       =>[int] breed holds the breedif of the pet
     *       =>[int] gender holds the genderid of the pet
     *       =>[date] dateOfBirth holds the date a pet was born in the format (yyyy-mm-dd)
     *       =>[real] weight holds the weight of the pet
     *       =>[real] height holds the height of the pet
     *       =>[int] length holds the length of the pet
     */
    public function Create(Request $request)
    {
        $validationResult = $this->app['api.petrequestvalidator']->ValidatePetCreationRequest($request);

        if (!$validationResult->GetSuccess()) {
            return $validationResult->GetError();
        }

        // Add pet to system and get back pet id
        $petID = $this->CreateGenericPet(
            $validationResult->GetParameter('name'),
            $validationResult->GetParameter('breed'),
            $validationResult->GetParameter('gender'),
            $validationResult->GetParameter('dateOfBirth'),
            $validationResult->GetParameter('weight'),
            $validationResult->GetParameter('height'),
            $validationResult->GetParameter('length')
        );

        if (!$petID) {
            return JsonResponse::userError('Unable to register pet.');
        }

        // Add animal specific parameters if necessary
        if ($validationResult->GetParameter('animalID') == 1) {
            $success = $this->AddPetCatDetails(
                $petID,
                $validationResult->GetParameter('declawed'),
                $validationResult->GetParameter('outdoor'),
                $validationResult->GetParameter('fixed')
            );

            if (!$success) {
                return JsonReponse::userError('Unable to register cat.');
            }
        }

        return new JsonResponse(null, 201);
    }


    public function GetAccessibilities()
    {
        //gets user session
        $user = $this->app['session']->get('user');

        $sql = 'SELECT p.petid, p.name, ac.firstname, ac.lastname, ac.email, a.access FROM accessibility a INNER JOIN pet p ON p.petid = a.petid INNER JOIN account ac ON a.userid = ac.userid WHERE a.petid IN (SELECT petid FROM pet WHERE ownerid = :userID)';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':userID' => $user['userId']
        ));

        $returnedResults = $stmt->fetchAll(PDO::FETCH_ASSOC);

        $results = array();
        $petid = -1;
        $petNum = -1;
        for ($i=0; $i < count($returnedResults) ; $i++) {
            if($returnedResults[$i]['petid'] != $petid) {
                $petid = $returnedResults[$i]['petid'];
                $petNum++;

                $content = array (
                    "petid" => $returnedResults[$i]['petid'],
                    "name" => $returnedResults[$i]['name'],
                    "shared" => array()
                );
                $shared = array(
                    "firstname" => $returnedResults[$i]['firstname'],
                    "lastname" => $returnedResults[$i]['lastname'],
                    "email" => $returnedResults[$i]['email'],
                    "access" => $returnedResults[$i]['access']
                );
                array_push($content['shared'],$shared);
                array_push($results, $content);
            }
            else {
                $shared = array(
                    "firstname" => $returnedResults[$i]['firstname'],
                    "lastname" => $returnedResults[$i]['lastname'],
                    "email" => $returnedResults[$i]['email'],
                    "access" => $returnedResults[$i]['access']
                );
                array_push($results[$petNum]['shared'],$shared);
            }
        }

        $body = array(
            "success" => true,
            "pets" => $results
        );
        return new JsonResponse($body,200);
    }


    /**
     * Function adds sharing of one pet to another user in the system
     * @param Request $request holds JSON data of user and pet info in order to share a pet with someone else
     *       =>[text] email holds the email in format (*@*.*)
     *       =>[int] petID hold the petID of a pet in the system
     *       =>[enum] access holds either 'write' OR 'read' to distiguish what access someone is gaining
     */
    public function SetAccessibility(Request $request)
    {
        $validationResult = $this->app['api.petrequestvalidator']->ValidateSetPetAccessibilityRequest($request);

        if (!$validationResult->GetSuccess()) {
            return $validationResult->GetError();
        }

        // Get userID from email
        $userID = $this->app['api.auth']->GetUserIDByEmail($validationResult->GetParameter('email'));

        if (!$userID) {
            return JsonResponse::userError('Email provided is not associated with an existing WellCat account');
        }

        // Check to see if user already has accessibility with pet
        $currentAccess = $this->GetPetAccessibility($userID, $validationResult->GetParameter('petID'));

        // If no accessibility found, insert
        if (!$currentAccess) {
            $sql = 'INSERT INTO accessibility (userid, petid, access)
                VALUES (:userid, :petid, :access)';

            $stmt = $this->app['db']->prepare($sql);
            $success = $stmt->execute(array(
                ':userid' => $userID,
                ':petid' => $validationResult->GetParameter('petID'),
                ':access' => $validationResult->GetParameter('access')
            ));

            if ($success) {
                return new JsonResponse(null, 201);
            }
            else {
                return JsonReponse::userError('Unable to set pet accessibility.');
            }
        }
        // else update if current accessibility is not the same as the one trying to be set
        elseif ($currentAccess != $validationResult->GetParameter('access')) {
            $sql = 'UPDATE accessibility
                    SET access = :access
                    WHERE userid = :userid
                        AND petid = :petid';

            $stmt = $this->app['db']->prepare($sql);
            $success = $stmt->execute(array(
                ':userid' => $userID,
                ':petid' => $validationResult->GetParameter('petID'),
                ':access' => $validationResult->GetParameter('access')
            ));

            if ($success) {
                return new JsonResponse(null, 201);
            }
            else {
                return JsonReponse::userError('Unable to update pet accessibility.');
            }
        }
        // else just return success
        else {
            return new JsonResponse();
        }
    }

    /**
     * Function removes sharing of one pet to another user in the system
     * @param Request $request holds JSON data of user and pet info in order to remove a pet share with someone else
     *       =>[text] email holds the email in format (*@*.*)
     *       =>[int] petID hold the petID of a pet in the system
     */
    public function RemoveAccessibility(Request $request)
    {
        $email = $request->request->get('email');
        $petID = $request->request->get('petID');
        // Get userID from email
        $userID = $this->app['api.auth']->GetUserIDByEmail($email);


        if (!$email) {
            return JsonResponse::missingParam('email');
        }
        elseif (!$petID) {
            return JsonResponse::missingParam('petID');
        }
        elseif (!$userID) {
            return JsonResponse::userError('Email provided is not associated with an existing WellCat account');
        }
        elseif (!is_int($petID)) {
            return JsonResponse::userError('Invlid petID');
        }
        elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
            return JsonResponse::userError('Invalid email');
        }
        elseif ($this->GetPetAccessibility($userID,$petID) == null) {
            return JsonResponse::userError('No pet share found');
        }

        $sql = 'DELETE FROM accessibility WHERE petid = :petID AND userid = :userID';
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':petID' => $petID,
            ':userID' => $userID
        ));

        if ($success) {
            return new JsonResponse(null,201);
        }
        else {
            $body = array(
                'success' => false,
                'error' => 'Unable to remove shared pet.'
            );
            return new JsonResponse($body,404);
        }
    }

    /**
    * Function updates any number of details for a specified AddPetCatDetails
    * @param Request $request holds JSON data of pet info to be updated
    *       =>[int] petID holds the petID of a pet in the system
    */
    public function UpdatePet(Request $request)
    {
        $validationResult = $this->app['api.petrequestvalidator']->ValidateUpdatePetRequest($request);

        if (!$validationResult->GetSuccess()) {
            return $validationResult->GetError();
        }

        // Check to see if user already has accessibility with pet (only the current owner can choose to change to a new owner)
        $accessLevel = $this->app['api.petservice']->CheckPetOwnership($validationResult->GetParameter('petID'), false);
        if (($validationResult->HasParameter('owner') && $accessLevel != 3)
            || $accessLevel < 2) {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );

            return new JsonResponse($body, 404);
        }

        // Begin db transaction
        try {
            $this->app['db']->beginTransaction();

            // Build sql statement
            $sql = 'UPDATE pet SET ';

            $sqlParameters = Array();

            if ($validationResult->HasParameter('owner')) {
                $sql = $sql . 'ownerid = :ownerID, ';
                $sqlParameters['ownerID'] = $this->app['api.auth']->GetUserIDByEmail($validationResult->GetParameter('owner'));
            }

            if ($validationResult->HasParameter('name')) {
                $sql = $sql . 'name = :name, ';
                $sqlParameters['name'] = $validationResult->GetParameter('name');
            }

            if ($validationResult->HasParameter('gender')) {
                $sql = $sql . 'gender = :gender, ';
                $sqlParameters['gender'] = $validationResult->GetParameter('gender');
            }

            if ($validationResult->HasParameter('dateOfBirth')) {
                $sql = $sql . 'dateOfBirth = :dateOfBirth, ';
                $sqlParameters['dateOfBirth'] = $validationResult->GetParameter('dateOfBirth');
            }

            if ($validationResult->HasParameter('weight')) {
                $sql = $sql . 'weight = :weight, ';
                $sqlParameters['weight'] = $validationResult->GetParameter('weight');
            }

            if ($validationResult->HasParameter('height')) {
                $sql = $sql . 'height = :height, ';
                $sqlParameters['height'] = $validationResult->GetParameter('height');
            }

            if ($validationResult->HasParameter('length')) {
                $sql = $sql . 'length = :length, ';
                $sqlParameters['length'] = $validationResult->GetParameter('length');
            }

            if ($validationResult->HasParameter('dateOfDeath')) {
                $sql = $sql . 'dateofdeath = :dateOfDeath, ';
                $sqlParameters['dateOfDeath'] = $validationResult->GetParameter('dateOfDeath');
            }

            if ($validationResult->HasParameter('reasonForDeath')) {
                $sql = $sql . 'reasonForDeath = :reasonForDeath, ';
                $sqlParameters['reasonForDeath'] = $validationResult->GetParameter('reasonForDeath');
            }

            if (count($sqlParameters) > 0) {
                $sql = rtrim($sql, ", ") . ' WHERE petID = :petID';
                $sqlParameters['petID'] = $validationResult->GetParameter('petID');

                // Execute update
                $stmt = $this->app['db']->prepare($sql);
                $success = $stmt->execute($sqlParameters);

                if (!$success) {
                    $this->app['db']->rollBack();
                    return JsonReponse::userError('Unable to update pet.');
                }
            }

            // Update cat specific parameters if necessary
            if ($this->app['api.petservice']->GetAnimalTypeIDFromPet($validationResult->GetParameter('petID')) == 1) {
                $sql = 'UPDATE pet_cat SET ';

                $sqlParameters = Array();

                if ($validationResult->HasParameter('declawed')) {
                    $sql = $sql . 'declawed = :declawed, ';
                    $sqlParameters['declawed'] = $validationResult->GetParameter('declawed');
                }

                if ($validationResult->HasParameter('outdoor')) {
                    $sql = $sql . 'outdoor = :outdoor, ';
                    $sqlParameters['outdoor'] = $validationResult->GetParameter('outdoor');
                }

                if ($validationResult->HasParameter('fixed')) {
                    $sql = $sql . 'fixed = :fixed, ';
                    $sqlParameters['fixed'] = $validationResult->GetParameter('fixed');
                }

                if (count($sqlParameters) > 0) {
                    $sql = rtrim($sql, ", ") . ' WHERE petID = :petID';
                    $sqlParameters['petID'] = $validationResult->GetParameter('petID');

                    // Execute update
                    $stmt = $this->app['db']->prepare($sql);
                    $success = $stmt->execute($sqlParameters);

                    if (!$success) {
                        $this->app['db']->rollBack();
                        return JsonReponse::userError('Unable to update pet.');
                    }
                }
            }

            $this->app['db']->commit();

            return new JsonResponse(null, 201);
        } catch (Exception $e) {
            $this->app['db']->rollBack();
            return JsonResponse::serverError();
        }
    }

    /**
     * Function adds a pet to the system
     * @param [string] $name holds the name of the pet
     * @param [int] $breed holds the breedID of the pet
     * @param [int] $gender holds the genderID of the pet
     * @param [string] $dateOfBirth holds a date string formatted as Y-m-d
     * @param [float] $weight holds the weight of the pet in kilograms (?)
     * @param [float] $height holds the height of the pet in cm (?)
     * @param [float] $length holds the length of the pet in cm (?)
     * @return [int] returns the id of the newly created pet; null if error occurred
    */
    private function CreateGenericPet($name, $breed, $gender, $dateOfBirth, $weight, $height, $length)
    {
        // Add pet to database
        $sql = 'INSERT INTO pet (ownerid, name, breed, gender, dateofbirth, weight, height, length)
                VALUES (:ownerId, :name, :breed, :gender, :dateOfBirth, :weight, :height, :length)
                RETURNING petid';

        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':ownerId' => $this->app['session']->get('user')['userId'],
            ':name' => $name,
            ':breed' => $breed,
            ':gender' => $gender,
            ':dateOfBirth' => $dateOfBirth,
            ':weight' => $weight,
            ':height' => $height,
            ':length' => $length
        ));

        if ($success) {
            $result = $stmt->fetch(\PDO::FETCH_ASSOC);

            return (int)$result['petid'];
        }
        else {
            return null;
        }
    }

    /**
     * Function takes an existing pet and adds cat specific parameters to the system
     * @param [int] $petID holds the petID of the existing pet cat
     * @param [bool] $declawed determines whether the cat is declawed or not
     * @param [bool] $outdoor determines whether the cat is an outdoor cat or not
     * @param [bool] $fixed determines whether the cat is fixed or not
     * @return [bool] returns true if successful, false otherwise
    */
    private function AddPetCatDetails($petID, $declawed, $outdoor, $fixed)
    {
        // Add cat to database
        $sql = 'INSERT INTO pet_cat (petid, declawed, outdoor, fixed)
                VALUES (:petID, :declawed, :outdoor, :fixed)';

        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':petID' => $petID,
            ':declawed' => $declawed,
            ':outdoor' => $outdoor,
            ':fixed' => $fixed
        ));

        return $success;
    }

    /**
     * Function gets pet information based on a given petID but if the user doesn't have
     * access they do not get any information about the pet
     * @param [int] $petID holds the petID of a pet to be accessed
    */
    public function GetPet($petID)
    {
        //gets user session
        $user = $this->app['session']->get('user');

        //checks if user owns the pet
        $sql = 'SELECT B.animaltypeid FROM pet P INNER JOIN breed B ON B.breedid = P.breed WHERE P.petid = :petID AND P.ownerid = :user';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':petID' => $petID,
            ':user' => $user['userId']
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        //if user doesn't own the pet checks to see if they have access to the
        //pet and if not a error message is returned to the caller
        if (!$result) {
            $sql = 'SELECT B.animaltypeid FROM accessibility A INNER JOIN pet P ON P.petid = A.petid INNER JOIN breed B ON B.breedid = P.breed WHERE A.userid = :user AND A.petid = :petID';
            $stmt = $this->app['db']->prepare($sql);
            $stmt->execute(array(
                ':petID' => $petID,
                ':user' => $user['userId']
            ));

            $result = $stmt->fetch(\PDO::FETCH_ASSOC);
            if (!$result) {
                $body = array(
                    'success' => false,
                    'error' => 'Pet not found'
                );

                return new JsonResponse ($body, 404);
            }
        }

        // Get pet + cat info
        if ((int)$result['animaltypeid'] == 1) {
            $sql = 'SELECT P.name, P.breed, P.gender, P.dateofbirth AS dateOfBirth, P.weight, P.height, P.length, PC.declawed, PC.outdoor, PC.fixed
                    FROM pet P
                        INNER JOIN pet_cat PC ON PC.petid = P.petid
                    WHERE P.petid = :petID;';
        }
        // Get generic pet info
        else {
            $sql = 'SELECT name, breed, gender, dateofbirth AS dateOfBirth, weight, height, length
                    FROM pet
                    WHERE petid = :petID;';
        }

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':petID' => $petID
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        $body = array(
            'success' => true,
            'pet' => $result
        );

        return new JsonResponse($body,200);

    }

    /**
     * Function gets a listing of all pets a user has access to and returns them
     */
    public function GetAllPets()
    {
        $user = $this->app['session']->get('user');

        //get list of all pets that the current user owns
        $sql = 'SELECT p.petid, p.name, p.gender, p.breed, a.firstname, a.lastname, p.lastupdated FROM pet p INNER JOIN account a ON p.ownerid = a.userid WHERE p.ownerid = :user ORDER BY p.petid ASC';

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':user' => $user['userId']
        ));

        $personal = $stmt->fetchAll(\PDO::FETCH_ASSOC);

        //get list of all pets that current user has access to.
        $sql = 'SELECT distinct on (p.petid) p.petid, p.name, p.gender, p.breed, a.firstname, a.lastname, ac.access, p.lastupdated FROM pet p INNER JOIN account a ON p.ownerid = a.userid INNER JOIN accessibility ac ON ac.petid = p.petid WHERE p.petid IN (SELECT f.petid FROM accessibility f WHERE f.userid = :user) ORDER BY p.petid ASC';

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':user' => $user['userId']
        ));

        $shared = $stmt->fetchAll(\PDO::FETCH_ASSOC);

        if ($personal || $shared) {
            $body = array(
                'success' => true,
                'personal' => $personal,
                'shared' => $shared
            );

            return new JsonResponse($body, 200);
        }
        else {
            $body = array(
                'success' => true,
                'message' => 'No pets found'
            );

            return new JsonResponse($body, 404);
        }
    }

    public function RemovePet(Request $request)
    {
        $petID = $request->request->get('petID');

        if (!$petID) {
            return JsonResponse::missingParam('petID');
        }
        elseif (!is_numeric($petID)) {
            return JsonResponse::userError('petID needs to be an int');
        }

        $ownership = $this->app['api.petservice']->CheckPetOwnership($petID,false);
        if($ownership != 3) {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );
            return new JsonResponse($body,401);
        }

        $sql = 'UPDATE pet SET visible = false WHERE petid = :petID';
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            'petID' => $petID
        ));

        if($success) {
            return new JsonResponse();
        }
        else {
            return JsonResponse::serverError();
        }


    }

    /**
     * Function trys to select a current shared access if it exits it returns the access. Otherwise returns null
     * @param [int] $userID holds a userID of a user in the system
     * @param [int] $petID  holds a petID of a pet in the system
     */
    private function GetPetAccessibility($userID, $petID)
    {
        // TODO: validate parameters and throw exception if null
        // For now, this function is only being called in a state where parameters have already been validated

        $sql = 'SELECT access FROM accessibility WHERE userid = :userid AND petid = :petid';

        $stmt= $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':userid' => $userID,
            ':petid' => $petID
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);
        if ($result) {
            return $result['access'];
        }
        else {
            return null;
        }
    }
}
