<?php
namespace WellCat\Controllers;

use PDO;
use DateTime;
use Silex\Application;
use Symfony\Component\HttpFoundation\Request;
use WellCat\JsonResponse;

class FitCatController
{
    protected $app;

    public function __construct(Application $app)
    {
        $this->app = $app;
        $this->app['session']->start();
    }

    public function Weight(Request $request)
    {
        $petID = $request->request->get('petID');
        $weight = $request->request->get('weight');
        $date = $request->request->get('date');
        
        // Validate parameters
        if (!$petID) {
            return JsonResponse::missingParam('petID');
        }
        elseif (!$weight) {
            return JsonResponse::missingParam('weight');
        }
        elseif (!$date) {
            return JsonResponse::missingParam('date');
        }
        elseif (!is_numeric($petID)) {
            return JsonResponse::userError('Invalid petID');
        }
        elseif (!is_numeric($weight)) {
            return JsonResponse::userError('Invalid weight');
        }
        elseif (!DateTime::createFromFormat('Y-m-d', $date)) {
            return JsonResponse::userError('Invalid date');
        }
        //first checks to see if petID is accessable by the user (write-access).
        elseif ($this->app['api.petservice']->CheckPetOwnership($petID,TRUE) < 2) {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );
            return new JsonResponse($body, 404);
        }

        $sql = 'UPDATE pet SET weight = :weight, lastupdated = now() WHERE petid = :petID';
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':weight' => $weight,
            ':petID' => $petID
        ));

        // Check if a row exists in the table for the day, for that specific pet
        $sql = 'SELECT NULL FROM fitcat WHERE petid = :petID AND date = :date';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':petID' => $petID,
            ':date' => $date
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        if ($result) {
            $sql = 'UPDATE fitcat SET weight = :weight WHERE petid = :petID AND date = :date';
        }
        else {
            $sql = 'INSERT INTO fitcat (petid, weight, date) VALUES (:petID, :weight, :date)';
        }
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':petID' => $petID,
            ':weight' => $weight,
            ':date' => $date
        ));

        if ($success) {
            return new JsonResponse(null,201);
        } 
        else {
            return JsonReponse::userError('Unable to update weight');
        }
    }
    
    public function Steps(Request $request)
    {
        $petID = $request->request->get('petID');
        $steps = $request->request->get('steps');
        $date = $request->request->get('date');
        
        // Validate parameters
        if (!$petID) {
            return JsonResponse::missingParam('petID');
        }
        elseif (!$steps) {
            return JsonResponse::missingParam('steps');
        }
        elseif (!$date) {
            return JsonResponse::missingParam('date');
        }
        elseif (!is_numeric($petID)) {
            return JsonResponse::userError('Invalid petID');
        }
        elseif (!is_numeric($steps)) {
            return JsonResponse::userError('Invalid steps');
        }
        elseif (!DateTime::createFromFormat('Y-m-d', $date)) {
            return JsonResponse::userError('Invalid date');
        }
        //first checks to see if petID is accessable by the user (write-access).
        elseif ($this->app['api.petservice']->CheckPetOwnership($petID,TRUE) < 2) {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );
            return new JsonResponse($body, 404);
        }

        // Check if a row exists in the table for the day, for that specific pet 
        $sql = 'SELECT NULL FROM fitcat WHERE petid = :petID AND date = :date';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array( 
            ':petID' => $petID,
            ':date' => $date
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);
            
        if ($result) {
            $sql = 'UPDATE fitcat SET steps = :steps WHERE petid = :petID AND date = :date';
        }
        else {      
            $sql = 'INSERT INTO fitcat (petid, steps, date) VALUES (:petID, :steps, :date)';
        }
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':petID' => $petID,
            ':steps' => $steps,
            ':date' => $date
        ));

        if ($success) {
            return new JsonResponse(null,201);
        } 
        else {
            return JsonReponse::userError('Unable to update steps');
        }
    }
    
    public function Water(Request $request)
    {
        $petID = $request->request->get('petID');
        $amount = $request->request->get('amount');
        $date = $request->request->get('date');
        
        // Validate parameters
        if (!$petID) {
            return JsonResponse::missingParam('petID');
        }
        elseif (!$amount) {
            return JsonResponse::missingParam('amount');
        }
        elseif (!$date) {
            return JsonResponse::missingParam('date');
        }
        elseif (!is_numeric($petID)) {
            return JsonResponse::userError('Invalid petID');
        }
        elseif (!is_numeric($amount)) {
            return JsonResponse::userError('Invalid water amount');
        }
        elseif (!DateTime::createFromFormat('Y-m-d', $date)) {
            return JsonResponse::userError('Invalid date');
        }
        //first checks to see if petID is accessable by the user (write-access).
        elseif ($this->app['api.petservice']->CheckPetOwnership($petID,TRUE) < 2) {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );
            return new JsonResponse($body, 404);
        }

        // Check if a row exists in the table for the day, for that specific pet 
        $sql = 'SELECT NULL FROM fitcat WHERE petid = :petID AND date = :date';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':petID' => $petID,
            ':date' => $date
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);
        
        if ($result) {
            $sql = 'UPDATE fitcat SET waterconsumption = :amount WHERE petid = :petID AND date = :date';
        }
        else {      
            $sql = 'INSERT INTO fitcat (petid, waterconsumption, date) VALUES (:petID, :amount, :date)';
        }
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':petID' => $petID,
            ':amount' => $amount,
            ':date' => $date
        )); 

        if ($success) {
            return new JsonResponse(null,201);
        } 
        else {
            return JsonReponse::userError('Unable to update water');
        }
    }
  
    public function Food(Request $request)
    {
        $petID = $request->request->get('petID');
        $brand = $request->request->get('brand');
        $name = $request->request->get('name');
        $amount = $request->request->get('amount');
        $description = $request->request->get('description');
        $date = $request->request->get('date');
        
        // Validate parameters
        if (!$petID) {
            return JsonResponse::missingParam('petID');
        }
        elseif (!$brand) {
            return JsonResponse::missingParam('brand');
        }
        elseif (!$name) {
            return JsonResponse::missingParam('name');
        }
        elseif (!$amount) {
            return JsonResponse::missingParam('amount');
        }
        elseif (!$description) {
            return JsonResponse::missingParam('description');
        }
        elseif (!$date) {
            return JsonResponse::missingParam('date');
        }
        elseif (!is_numeric($petID)) {
            return JsonResponse::userError('Invalid petID');
        }
        elseif (!is_numeric($amount)) {
            return JsonResponse::userError('Invalid food amount');
        }
        elseif (!DateTime::createFromFormat('Y-m-d', $date)) {
            return JsonResponse::userError('Invalid date');
        }
        //first checks to see if petID is accessable by the user (write-access).
        elseif ($this->app['api.petservice']->CheckPetOwnership($petID,TRUE) < 2) {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );
            return new JsonResponse($body, 404);
        }

        // Check if a row exists in the table for the day, for that specific pet 
        $sql = 'SELECT NULL FROM fitcat WHERE petid = :petID AND date = :date';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':petID' => $petID,
            ':date' => $date
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        if ($result) {
            $sql = 'UPDATE fitcat SET foodconsumption = :amount, foodbrand = :brand, description = :description, name = :name WHERE petid = :petID AND date = :date';
        }
        else {
            $sql = 'INSERT INTO fitcat (petid, foodconsumption, foodbrand, description, name, date) VALUES (:petID, :amount, :brand, :description, :name, :date)';
        }
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':petID' => $petID,
            ':amount' => $amount,
            ':brand' => $brand,
            ':description' => $description,
            ':name' => $name,
            ':date' => $date
        ));

        if ($success) {
            return new JsonResponse(null,201);
        } 
        else {
            return JsonReponse::userError('Unable to update food');
        }
    }   

    public function Pets()
    {
        $user = $this->app['session']->get('user');
        
        //Get all pet/fitcat data for personal cats
        $sql = 'SELECT p.petid, p.name, p.gender, p.breed, a.firstname, a.lastname, p.lastupdated FROM pet p INNER JOIN account a ON p.ownerid = a.userid WHERE p.ownerid = :user AND p.fitcat=true ORDER BY p.petid ASC';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':user' => $user['userId']
        ));
        $personal = $stmt->fetchAll(\PDO::FETCH_ASSOC);

        //Get all pet/fitcat data for shared cats
        $sql = 'SELECT distinct on (p.petid) p.petid, p.name, p.gender, p.breed, a.firstname, a.lastname, ac.access, p.lastupdated FROM pet p INNER JOIN account a ON p.ownerid = a.userid INNER JOIN accessibility ac ON ac.petid = p.petid WHERE p.fitcat=true AND p.petid IN (SELECT f.petid FROM accessibility f WHERE f.userid = :user) ORDER BY p.petid ASC';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':user' => $user['userId']
        ));
        $shared = $stmt->fetchAll(\PDO::FETCH_ASSOC);

        if ($personal || $shared) {
            $body = array(
                'success' => true,
                'personal' => $personal,
                'shared' => $shared,
            );

            return new JsonResponse($body, 200);
        }
        else {
            $body = array(
                'success' => false,
                'error' => 'No pets found'
            );
            return new JsonResponse($body, 404);
        }
    }

    public function View($petID)
    {
        //first checks to see if petID is accessable by the user.
        if (!$this->app['api.petservice']->CheckPetOwnership($petID,TRUE)) {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );
            return new JsonResponse($body, 404);
        }

        
        $sql = 'SELECT weight, steps, waterconsumption, foodconsumption, foodbrand, description, name, date FROM fitcat WHERE petid = :petID ORDER BY date DESC';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array( 
            ':petID' => $petID
        ));

        $fitcatResults = $stmt->fetchAll(\PDO::FETCH_ASSOC);

        //gets the animal type
        $sql = 'SELECT B.animaltypeid FROM breed B INNER JOIN pet P ON P.breed = B.breedid WHERE P.petid = :petID';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array( 
            ':petID' => $petID
        ));
        $result = $stmt->fetch(\PDO::FETCH_ASSOC);
        

        // Get pet + cat info
        if ((int)$result['animaltypeid'] == 1) {
            $sql = 'SELECT P.name, P.breed, P.gender, P.dateofbirth, P.weight, P.height, P.length, PC.declawed, PC.outdoor, PC.fixed, P.lastupdated FROM pet P INNER JOIN pet_cat PC ON PC.petid = P.petid WHERE P.petid = :petID;';
        }
        // Get generic pet info
        else {
            $sql = 'SELECT name, breed, gender, dateofbirth, weight, height, length, lastupdated FROM pet WHERE petid = :petID;';
        }

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            ':petID' => $petID
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        if ($result) {
            $body = array(
                'success' => true,
                'pet' => $result,
                'fitcat' => $fitcatResults
            );

            return new JsonResponse($body,200);
        }
        else {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );
            return new JsonResponse($body, 404);
        }

    }

    public function Register(Request $request)
    {
        //gets parameters
        $petID = $request->request->get('petID');

        //validates parameters
        if (!$petID) {
            return JsonResponse::missingParam('petID');
        }
        elseif (!is_numeric($petID)) {
            return JsonResponse::userError('Invalid petID');
        }
        elseif ($this->app['api.petservice']->CheckPetOwnership($petID,FALSE) != 3) {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );
            return new JsonResponse($body, 404);
        }

        $sql = 'UPDATE pet SET fitcat = TRUE WHERE petid = :petID';
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':petID' => $petID
        ));

        if ($success) {
            return new JsonResponse(null,201);
        }
        else {
            return JsonResponse::serverError();
        }

    }


    public function DeRegister(Request $request)
    {
        //gets parameters
        $petID = $request->request->get('petID');

        //validates parameters
        if (!$petID) {
            return JsonResponse::missingParam('petID');
        }
        elseif (!is_numeric($petID)) {
            return JsonResponse::userError('Invalid petID');
        }
        elseif ($this->app['api.petservice']->CheckPetOwnership($petID,TRUE) != 3) {
            $body = array(
                'success' => false,
                'error' => 'Pet not found'
            );
            return new JsonResponse($body, 404);
        }

        $sql = 'UPDATE pet SET fitcat = FALSE WHERE petid = :petID';
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':petID' => $petID
        ));

        if ($success) {
            return new JsonResponse(null,201);
        }
        else {
            return JsonResponse::serverError();
        }
    }
}





