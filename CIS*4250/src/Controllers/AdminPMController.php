<?php

namespace WellCat\Controllers;

use Silex\Application;
use PDO;
use DateTime;
use Symfony\Component\HttpFoundation\Request;
use WellCat\JsonResponse;

class AdminPMController
{

    protected $app;

    public function __construct(Application $app)
    {
        $this->app = $app;
        $this->app['session']->start();
    }


    /**
     * Function tells the user they are authenticated.
     */
    public function Authenticate()
    {
        $data = array(
            'success' => true,
            'message' => 'Successfully authenticated'
        );
        return new JsonResponse($data, 200);
    }

    public function Create(Request $request)
    {
        $user = $this->app['session']->get('user');

        $ownerEmail = $request->request->get('owner');
        $petName = $request->request->get('name');
        $dateOfBirth = $request->request->get('dateOfBirth');
        $weight = $request->request->get('weight');
        $height = $request->request->get('height');
        $length = $request->request->get('length');
        $animal = $request->request->get('animalTypeID');
        $breed = $request->request->get('breed');
        $gender = $request->request->get('gender');

        // Validate parameters
        if (!$ownerEmail) {
            return JsonResponse::missingParam('owner');
        }
        elseif (!$petName) {
            return JsonResponse::missingParam('name');
        }
        elseif (!$breed) {
            return JsonResponse::missingParam('breed');
        }
        elseif (!$animal) {
            return JsonResponse::missingParam('animalTypeID');
        }
        elseif (!$gender) {
            return JsonResponse::missingParam('gender');
        }
        elseif (!$dateOfBirth) {
            return JsonResponse::missingParam('dateOfBirth');
        }
        elseif (!$weight) {
            return JsonResponse::missingParam('weight');
        }
        elseif (!$height) {
            return JsonResponse::missingParam('height');
        }
        elseif (!$length) {
            return JsonResponse::missingParam('length');
        }
        elseif(!$this->app['api.animalservice']->CheckAnimalExists($animal)) {
            return JsonResponse::userError('animal needs to be a int and valid');
        }
        elseif(!is_string($petName)) {
            return JsonResponse::userError('name needs to be a string');
        }
        elseif(!$this->app['api.animalservice']->CheckGenderExists($gender)) {
            return JsonResponse::userError('gender  needs to be a int and valid');
        }
        elseif (!DateTime::createFromFormat('Y-m-d', $dateOfBirth)) {
            return JsonResponse::userError('Invalid date.');
        }
        elseif (!$this->app['api.animalservice']->CheckBreedExists($breed)) {
            return JsonResponse::userError('breed needs to be a int and valid');
        }
        elseif(!is_numeric($weight)) {
            return JsonResponse::userError('weight needs to be a number');
        }
        elseif(!is_numeric($height)) {
            return JsonResponse::userError('height needs to be a number');
        }
        elseif(!is_numeric($length)) {
            return JsonResponse::userError('length needs to be a number');
        }
        elseif (!filter_var($ownerEmail, FILTER_VALIDATE_EMAIL)) {
            return JsonResponse::userError('Invalid email');
        }

        $ownerID = $this->app['api.auth']->GetUserIDByEmail($ownerEmail);

        if ($ownerID == null) {
            return JsonResponse::userError('Email not found');
        }
        
        // Add pet to database
        $sql = 'INSERT INTO pet (ownerid, name, breed, gender, dateofbirth, weight, height, length) VALUES (:ownerID, :name, :breed, :gender, :dateOfBirth, :weight, :height, :length)';

        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':ownerID' => $ownerID,
            ':name' => $petName,
            ':breed' => $breed,
            ':gender' => $gender,
            ':dateOfBirth' => $dateOfBirth,
            ':weight' => $weight,
            ':height' => $height,
            ':length' => $length
        ));

        if ($success && $animal == 1) {
            //get petID from previous entry
            $petID = $this->app['db']->lastInsertId('pet_petid_seq');

            // Add cat to database
            $sql = 'INSERT INTO pet_cat (petid, declawed, outdoor, fixed) VALUES (:petID, :declawed, :outdoor, :fixed)';

            $stmt = $this->app['db']->prepare($sql);
            $success = $stmt->execute(array(
                ':petID' => $petID,
                ':declawed' => "true",
                ':outdoor' => "false",
                ':fixed' => "true"
            ));

            if ($success) {
                return new JsonResponse(null,201);
            }
            else {
                //TODO: Need to remove the pet if it fails to add it originally.
                return JsonResponse::userError('Unable to create pet.');
            }
        }
        elseif($success) {
            return new JsonResponse(null,201);
        }
        else {          
            return JsonResponse::userError('Unable to register pet.');
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


        // Begin db transaction
        try {
            $this->app['db']->beginTransaction();

            //attempts to get the pet type. If it cannot the pet desn't exist and an error is thrown.
            $petType = $this->app['api.petservice']->GetAnimalTypeIDFromPet($validationResult->GetParameter('petID'));

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
            if ($petType == 1) {
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
}