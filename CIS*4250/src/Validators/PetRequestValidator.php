<?php

namespace WellCat\Validators;

use DateTime;
use Silex\Application;
use Symfony\Component\HttpFoundation\Request;
use WellCat\JsonResponse;
use WellCat\Converters\StringToBooleanConverter;

class PetRequestValidator
{
    protected $app;

    public function __construct(Application $app)
    {
        $this->app = $app;
    }

    public function ValidatePetCreationRequest(Request $request)
    {
        $success = true;
        $error = null;
        $parameters = null;

        // Get parameters
        $name = $request->request->get('name');
        $animalID = $request->request->get('animalTypeID');
        $breed = $request->request->get('breed');
        $gender = $request->request->get('gender');
        $dateOfBirth = $request->request->get('dateOfBirth');
        $weight = $request->request->get('weight');
        $height = $request->request->get('height');
        $length = $request->request->get('length');

        // Validate parameters
        if (!$name) {
            $success = false;
            $error = JsonResponse::missingParam('name');
        }
        elseif (!$animalID) {
            $success = false;
            $error = JsonResponse::missingParam('animalTypeID');
        }
        elseif (!$breed) {
            $success = false;
            $error = JsonResponse::missingParam('breed');
        }
        elseif (!$gender) {
            $success = false;
            $error = JsonResponse::missingParam('gender');
        }
        elseif (!$dateOfBirth) {
            $success = false;
            $error = JsonResponse::missingParam('dateOfBirth');
        }
        elseif (!$weight) {
            $success = false;
            $error = JsonResponse::missingParam('weight');
        }
        elseif (!$height) {
            $success = false;
            $error = JsonResponse::missingParam('height');
        }
        elseif (!$length) {
            $success = false;
            $error = JsonResponse::missingParam('length');
        }
        elseif (!is_string($name)) {
            $success = false;
            $error = JsonResponse::userError('name needs to be a string');
        }
        elseif(!$this->app['api.animalservice']->CheckAnimalExists($animalID)) {
            $success = false;
            $error = JsonResponse::userError('animal needs to be a int and valid');
        }
        elseif(!$this->app['api.animalservice']->CheckGenderExists($gender)) {
            $success = false;
            $error = JsonResponse::userError('gender  needs to be a int and valid');
        }
        elseif(!is_numeric($weight)) {
            $success = false;
            $error = JsonResponse::userError('weight needs to be a number');
        }
        elseif(!is_numeric($height)) {
            $success = false;
            $error = JsonResponse::userError('height needs to be a number');
        }
        elseif(!is_numeric($length)) {
            $success = false;
            $error = JsonResponse::userError('length needs to be a number');
        }
        elseif (!DateTime::createFromFormat('Y-m-d', $dateOfBirth)) {
            $success = false;
            $error = JsonResponse::userError('Invalid date.');
        }
        elseif (!$this->app['api.animalservice']->CheckBreedExists($breed)) {
            $success = false;
            $error = JsonResponse::userError('Invalid breed.');
        }
        else {
            $parameters = Array(
                'name' => $name,
                'animalID' => $animalID,
                'breed' => $breed,
                'gender' => $gender,
                'dateOfBirth' => $dateOfBirth,
                'weight' => $weight,
                'height' => $height,
                'length' => $length
            );
        }

        // Validate animal specific parameters if necessary
        if ((int)$animalID == 1 && $success == true) {
            $catValidationResult = $this->ValidatePetCatCreationRequest($request);

            if (!$catValidationResult->GetSuccess()) {
                $success = $catValidationResult->GetSuccess();
                $error = $catValidationResult->GetError();
            }
            else {
                $parameters = array_merge($parameters, $catValidationResult->GetParameters());
            }
        }

        return new RequestValidationResult($success, $parameters, $error);
    }

    private function ValidatePetCatCreationRequest(Request $request)
    {
        $success = true;
        $error = null;
        $parameters = null;

        // Get parameters
        $declawed = $request->request->get('declawed');
        $outdoor = $request->request->get('outdoor');
        $fixed = $request->request->get('fixed');

        // Validate parameters
        if (!$declawed) {
            $success = false;
            $error = JsonResponse::missingParam('declawed');
        }
        elseif (!$outdoor) {
            $success = false;
            $error = JsonResponse::missingParam('outdoor');
        }
        elseif (!$fixed) {
            $success = false;
            $error = JsonResponse::missingParam('fixed');
        }
        else {
            $parameters = Array(
                'declawed' => $declawed,
                'outdoor' => $outdoor,
                'fixed' => $fixed
            );
        }

        return new RequestValidationResult($success, $parameters, $error);
    }

    public function ValidateSetPetAccessibilityRequest(Request $request)
    {
        $success = true;
        $error = null;
        $parameters = null;

        // Get parameters
        $email = $request->request->get('email');
        $petID = $request->request->get('petID');
        $access = $request->request->get('access');

        // Validate parameters
        if (!$email) {
            $success = false;
            $error = JsonResponse::missingParam('email');
        }
        elseif (!$petID) {
            $success = false;
            $error = JsonResponse::missingParam('petID');
        }
        elseif (!$access) {
            $success = false;
            $error = JsonResponse::missingParam('access');
        }
        elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
            $success = false;
            $error = JsonResponse::userError('Invalid email');
        }
        elseif (!$this->app['api.dbtypes']->IsValidPetAccessibilityValue($access)) {
            $success = false;
            $error = JsonResponse::userError('Invalid accessibility value');
        }
        else {
            $parameters = Array(
                'petID' => $petID,
                'email' => $email,
                'access' => $access
            );
        }

        return new RequestValidationResult($success, $parameters, $error);
    }

    public function ValidateUpdatePetRequest(Request $request)
    {
        $parameters = Array();

        // Get parameters
        $petID = $request->request->get('petID');
        $owner = $request->request->get('owner');
        $name = $request->request->get('name');
        $breed = $request->request->get('breed');
        $gender = $request->request->get('gender');
        $dateOfBirth = $request->request->get('dateOfBirth');
        $weight = $request->request->get('weight');
        $height = $request->request->get('height');
        $length = $request->request->get('length');
        $dateOfDeath = $request->request->get('dateOfDeath');
        $reasonForDeath = $request->request->get('reasonForDeath');

        // Ensure we have a petID
        if (!$petID) {
            return new RequestValidationResult(false, null, JsonResponse::missingParam('petID'));
        }
        elseif (!is_numeric($petID)) {
            return new RequestValidationResult(false, null, JsonResponse::userError('Invalid petID'));
        }
        else {
            $parameters['petID'] = $petID;
        }

        // Validate parameters (we only need at least one valid parameter for this request)
        if (isset($owner)) {
            if (filter_var($owner, FILTER_VALIDATE_EMAIL)) {
              if (!is_null($this->app['api.auth']->GetUserIDByEmail($owner))) {
                  $parameters['owner'] = $owner;
              }
              else {
                $body = array(
                    'success' => false,
                    'error' => 'Owner not found'
                );

                return new RequestValidationResult(false, null, new JsonResponse($body, 400));
              }
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid owner email'));
            }
        }

        if (isset($name)) {
            if (is_string($name) && !empty($name)) {
                $parameters['name'] = $name;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid name'));
            }
        }

        if (isset($breed)) {
            if (is_numeric($breed)) {
                $parameters['breed'] = $breed;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid breed'));
            }
        }

        if (isset($gender)) {
            if (is_numeric($gender)) {
                $parameters['gender'] = $gender;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid gender'));
            }
        }

        if (isset($dateOfBirth)) {
            if (DateTime::createFromFormat('Y-m-d', $dateOfBirth)) {
                $parameters['dateOfBirth'] = $dateOfBirth;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid date of birth'));
            }
        }

        if (isset($weight)) {
            if (is_real($weight) || is_numeric($weight)) {
                $parameters['weight'] = $weight;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid weight'));
            }
        }

        if (isset($height)) {
            if (is_real($height) || is_numeric($height)) {
                $parameters['height'] = $height;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid height'));
            }
        }

        if (isset($length)) {
            if (is_real($length) || is_numeric($length)) {
                $parameters['length'] = $length;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid length'));
            }
        }

        if (isset($dateOfDeath)) {
            if (DateTime::createFromFormat('Y-m-d', $dateOfDeath)) {
                $parameters['dateOfDeath'] = $dateOfDeath;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid date of death'));
            }
        }

        if (isset($reasonForDeath)) {
            if (is_string($reasonForDeath) && !empty($reasonForDeath)) {
                $parameters['reasonForDeath'] = $reasonForDeath;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid reason for death'));
            }
        }

        // Check to see if cat specific parameters need to be validated
        if ($this->app['api.petservice']->GetAnimalTypeIDFromPet($petID) == 1) {
            $catValidationResult = $this->ValidateUpdatePetCatRequest($request);

            if (!$catValidationResult->GetSuccess()) {
                return $catValidationResult;
            }
            else {
                $parameters = array_merge($parameters, $catValidationResult->GetParameters());
            }
        }

        if (count($parameters) > 1) {
            return new RequestValidationResult(true, $parameters);
        }
        else {
            return new RequestValidationResult(false, null, JsonResponse::userError('At least one parameter must be set'));
        }
    }

    private function ValidateUpdatePetCatRequest(Request $request)
    {
        $parameters = Array();

        // Get parameters
        $declawed = $request->request->get('declawed');
        $outdoor = $request->request->get('outdoor');
        $fixed = $request->request->get('fixed');

        // Validate parameters
        if (isset($declawed)) {
            if (is_bool($declawed) || (is_string($declawed) && !is_null(StringToBooleanConverter::Convert($declawed)))) {
                $parameters['declawed'] = $declawed;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid declawed value'));
            }
        }

        if (isset($outdoor)) {
            if (is_bool($outdoor) || (is_string($outdoor) && !is_null(StringToBooleanConverter::Convert($outdoor)))) {
                $parameters['outdoor'] = $outdoor;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid outdoor value'));
            }
        }

        if (isset($fixed)) {
            if (is_bool($fixed) || (is_string($fixed) && !is_null(StringToBooleanConverter::Convert($fixed)))) {
                $parameters['fixed'] = $fixed;
            }
            else {
                return new RequestValidationResult(false, null, JsonResponse::userError('Invalid fixed value'));
            }
        }

        return new RequestValidationResult(true, $parameters);
    }
}
