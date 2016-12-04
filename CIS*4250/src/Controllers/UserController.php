<?php

namespace WellCat\Controllers;

use Silex\Application;
use PDO;
use Symfony\Component\HttpFoundation\Request;
use WellCat\JsonResponse;

class UserController
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


    /**
     * Function registers user in the system
     * @param Request $request holds JSON data of a user to register them in the system
     *       =>[text] email holds the email of a person in the format (*@*.*)
     *       =>[text] password holds the plain text of a password
     *       =>[text] firstName holds the first name of the new user
     *       =>[text] lastName holds the last name of the new user
     *       =>[array] address holds the address information of a user
     *                =>[street][text] holds the street adderss of the user
     *                =>[unit][text] holds the unit number of the user
     *                =>[city][text] holds the city name of the location the user is addressing
     *                =>[postalCode][text] holds the postal code of the user
     *                =>[locationID][int] holds a locationID that the user lives in
     */
    public function Register(Request $request)
    {
        //gets parameters
        $email = $request->request->get('email');
        $password = $request->request->get('password');
        $first = $request->request->get('firstName');
        $last = $request->request->get('lastName');
        $address = $request->request->get('address');

        //checks parameters for accuracy and existence
        if (!$email) {
            return JsonResponse::missingParam('email');
        }
        elseif (!$password) {
            return JsonResponse::missingParam('password');
        }
        elseif (!$first) {
            return JsonResponse::missingParam('firstName');
        }
        elseif (!$last) {
            return JsonResponse::missingParam('lastName');
        }
        elseif (!$address) {
            return JsonResponse::missingParam('address');
        }
        elseif (!$address['street']) {
            return JsonResponse::missingParam('address(street)');
        }
        elseif (!$address['unit']) {
            return JsonResponse::missingParam('address(unit)');
        }
        elseif (!$address['city']) {
            return JsonResponse::missingParam('address(city)');
        }
        elseif (!$address['postalCode']) {
            return JsonResponse::missingParam('address(postalCode)');
        }
        elseif (!$address['locationID']) {
            return JsonResponse::missingParam('address(locationID)');
        }
        elseif (!is_string($password)) {
            return JsonResponse::userError('password needs to be a string');
        }
        elseif (!is_string($first)) {
            return JsonResponse::userError('firstName needs to be a string');
        }
        elseif (!is_string($last)) {
            return JsonResponse::userError('lastName needs to be a string');
        }
        elseif (!is_string($address['street'])) {
            return JsonResponse::userError('address[\'street\'] needs to be a string');
        }
        elseif (!is_string($address['unit'])) {
            return JsonResponse::userError('address[\'unit\'] needs to be a string');
        }
        elseif (!is_string($address['city'])) {
            return JsonResponse::userError('address[\'city\'] needs to be a string');
        }
        elseif (!is_string($address['postalCode'])) {
            return JsonResponse::userError('address[\'postalCode\'] needs to be a string');
        }
        elseif (!is_numeric($address['locationID'])) {
            return JsonResponse::userError('address[\'locationID\'] needs to be an integer');
        }
        elseif (!$this->app['api.address']->CheckLocation($address['locationID'])) {
            return JsonResponse::userError('address[\'locationID\'] not found');
        }
        elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
            return JsonResponse::userError('Invalid email');
        } 

        /*
        Will add in later.

        elseif (!$this->app['api.auth']->passwordRequirements($pass)) {
            return JsonResponse::userError('Password requirements not met');
        }
        */
       
       //checks to see if the email is already registered with another user
        $sql = 'SELECT email FROM account WHERE email = :email';
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':email' => $email
        ));

        //if success is not good the querry failed.
        if (!$success) {
            return JsonReponse::userError('Unable to register');
        } 
        //Checks to see if there were any returned values and if so the email already exists
        else if ($stmt->fetch(PDO::FETCH_ASSOC) != false) {
            $body = array(
                'success' => false,
                'error' => 'Email already in use'
            );
            return new JsonResponse($body, 404);
        }

        //attempts to register given user address if fails returns -1. If successful returns a value >= 0
        $addressID = $this->app['api.address']->Register($address);
        if ($addressID == -1) {
            return JsonResponse::userError('Unable to register address');
        }

        //encrypts the password
        $encryptedPassword = $this->app['api.auth']->EncryptPassword($password);
        
        //adds the user to the system (registers them)
        $sql = 'INSERT INTO account (addressid, email, password, firstname, lastname)
            VALUES (:addressid, :email, :password, :first, :last)';
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':addressid' => (int)$addressID,
            ':email' => $email,
            ':password' => $encryptedPassword,
            ':first' => $first,
            ':last' => $last
        ));

        if ($success) {
            return new JsonResponse();
        } 
        else {
            return JsonReponse::userError('Unable to register');
        }
    }


    /**
     * Function logs in the user if the proper email and password are given
     * @param Request $request holds JSON data of the users email and password to login
     *       =>[text] email holds the email of the user attempting to login
     *       =>[text] password holds the password of the user attempting to login
     */
    public function Login(Request $request)
    {
        //gets parameters
        $email = $request->request->get('email');
        $password = $request->request->get('password');

        //checks parameters for accuracy and existence
        if (!$email) {
            return JsonResponse::missingParam('email');
        }
        elseif (!$password) {
            return JsonResponse::missingParam('password');
        }
        elseif (!is_string($password)) {
            return JsonResponse::userError('password needs to be a string');
        }
        elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
            return JsonResponse::userError('Invalid email');
        }

        //trys to log the user in (authenticate)
        $success = $this->app['api.auth']->Authenticate($email, $password);

        if ($success) {
            return new JsonResponse();
        } 
        else {
            return JsonResponse::authError('Incorrect email or password',401);
        }
    }


    /**
     * Function takes in the current password of a user and a new pasword to 
     * change to and attempts to update it if the passwords are correct.
     * @param Request $request holds JSON data of two passwords one current one new
     *       =>[text] currentPassword holds the current password the user has entered
     *       =>[text] newPassword holds the new password the user wants to update their password to
     */
    public function ChangePassword(Request $request)
    {
        $oldPassword = $request->request->get('currentPassword');
        $newPassword = $request->request->get('newPassword');
        $user = $this->app['session']->get('user');

        if (!$oldPassword) {
            return JsonResponse::missingParam('currentPassword');
        }
        elseif (!$newPassword) {
            return JsonResponse::missingParam('newPassword');
        }
        elseif (!is_string($oldPassword)) {
            return JsonResponse::userError('oldPassword needs to be a string');
        }
        elseif (!is_string($newPassword)) {
            return JsonResponse::userError('newPassword needs to be a string');
        }


        /*
        Will add in later.

        elseif (!$this->app['api.auth']->passwordRequirements($newPassword)) {
            return JsonResponse::userError('Password requirements not met');
        }
        */

        //Checks password to make sure it is valid for current user.
        $success = $this->app['api.auth']->CheckPassword($user['email'], $oldPassword);

        if ($success) {
            $encryptedPassword = $this->app['api.auth']->EncryptPassword($newPassword);

            $sql = 'UPDATE account SET password = :pass WHERE email = :email';
            $stmt = $this->app['db']->prepare($sql);
            $success = $stmt->execute(array(
                ':pass' => $encryptedPassword,
                ':email' => $user['email']
            ));

            return new JsonResponse();
        }
        else {
            return JsonResponse::authError('Invalid User or Password',401);
        }
    }

    public function UpdateUsr(Request $request)
    {

        $password = $request->request->get('password');
        $phone = $request->request->get('phoneNumber');
        $address = $request->request->get('address');
        $user = $this->app['session']->get('user');
        
        //valadate user input
        if (!$password) {
            return JsonResponse::missingParam('password');
        }
        elseif (!$address) {
            return JsonResponse::missingParam('address');
        }
        elseif (!$phone) {
            return JsonResponse::missingParam('phoneNumber');
        }
        elseif (!$address['street']) {
            return JsonResponse::missingParam('address(street)');
        }
        elseif (!$address['unit']) {
            return JsonResponse::missingParam('address(unit)');
        }
        elseif (!$address['city']) {
            return JsonResponse::missingParam('address(city)');
        }
        elseif (!$address['postalCode']) {
            return JsonResponse::missingParam('address(postalCode)');
        }
        elseif (!$address['locationID']) {
            return JsonResponse::missingParam('address(locationID)');
        }
        elseif (!is_string($phone)) {
            return JsonResponse::userError('phoneNumber needs to be a string');
        }
        elseif (!is_string($password)) {
            return JsonResponse::userError('password needs to be a string');
        }
        elseif (!is_string($address['street'])) {
            return JsonResponse::userError('address[\'street\'] needs to be a string');
        }
        elseif (!is_string($address['unit'])) {
            return JsonResponse::userError('address[\'unit\'] needs to be a string');
        }
        elseif (!is_string($address['city'])) {
            return JsonResponse::userError('address[\'city\'] needs to be a string');
        }
        elseif (!is_string($address['postalCode'])) {
            return JsonResponse::userError('address[\'postalCode\'] needs to be a string');
        }
        elseif (!is_numeric($address['locationID'])) {
            return JsonResponse::userError('address[\'locationID\'] needs to be an integer');
        }
        elseif (!$this->app['api.address']->CheckLocation($address['locationID'])) {
            return JsonResponse::userError('address[\'locationID\'] not found');
        }

        $success = $this->app['api.auth']->CheckPassword($user['email'], $password);

        if ($success) {

            //update address table with user submitted information
            $sql = 'UPDATE address SET locationid = :locationid, city = :city, street = :street, unit = :unit,  postalcode = :postalcode FROM account WHERE account.addressid = address.addressid AND account.userid = :userid';

            //update address information
            $stmt = $this->app['db']->prepare($sql);
            $submited = $stmt->execute(array(
                ':locationid' => $address['locationID'],
                ':city' => $address['city'],
                ':street' => $address['street'],
                ':unit' => $address['unit'],
                ':postalcode' => $address['postalCode'],
                ':userid' => $user['userId']
            ));

            //update account information only for phone
            $sql = 'UPDATE account SET phonenumber = :phone WHERE account.userid = :userid';

            $stmt = $this->app['db']->prepare($sql);
            $submited = $stmt->execute(array(
                ':phone' => $phone,
                ':userid' => $user['userId']
            ));

            // return response
            if($submited){
                 $data = array(
                    'success' => true,
                    'message' => 'user updated'
                 );
                 return new JsonResponse($data, 201);
            }
            else {
                //sql update failed
                return JsonReponse::userError('Unable to update');
            }
        } 
        else {
            // user not logged in
            return JsonResponse::authError('Invalid User or Password',401);
        }
    }


    public function ViewUsr()
    {
        $user = $this->app['session']->get('user');

        //select data form address and account related to our current user
        $sql = 'SELECT email, firstname, lastname, phonenumber, street, city, unit, locationid, postalcode FROM address s INNER JOIN account a ON a.addressid = s.addressid WHERE email = :email';
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
             ':email' => $user['email']
        ));

        $result = $stmt->fetch(PDO::FETCH_ASSOC);

        //return results 
        if ($result) {
            $data = array(
                'success' => true,
                'userinfo' => $result
            );
            return new JsonResponse($data, 200);

        }
        else {
            return JsonResponse::authError('Invalid User',401);

        }

    }


    public function Logout() {
        $user = $this->app['session']->get('user');

        if($this->app['api.auth']->Authenticated() == false) {
            session_destroy();
            return JsonResponse::authError('User not authenticated', 401);
        }

        session_destroy();
        return new JsonResponse();
    }
}
