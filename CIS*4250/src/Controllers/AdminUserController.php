<?php

namespace WellCat\Controllers;

use Silex\Application;
use PDO;
use Symfony\Component\HttpFoundation\Request;
use WellCat\JsonResponse;

class AdminUserController
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

    public function View($userID)
    {
        // select a single user from the database
        $sql = 'SELECT email, firstname, lastname, phonenumber, street, city, unit, locationid, postalcode FROM address s INNER JOIN account a ON a.addressid = s.addressid WHERE userid = :userID';

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(':userID' => $userID));

        $results = $stmt->fetch(PDO::FETCH_ASSOC);

        $body = array(
            "success" => true,
            "userinfo" => $results
        );
        
        if($results) {
            return new JsonResponse($body,200);
        }
        else {          
            return JsonResponse::userError('No Users Found.');
        }
    }

    public function Search(Request $request)
    {
        $user = $this->app['session']->get('user');

        $parameters = array();
        
        
        // Select all users that are relevant.
        $sql = 'SELECT userid, email, firstname, lastname FROM account';

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute($parameters);

        $results = $stmt->fetchAll(PDO::FETCH_ASSOC);

        $body = array(
            "success" => true,
            "users" => $results
        );
        
        if($results) {
            return new JsonResponse($body,200);
        }
        else {          
            return JsonResponse::userError('No Users Found.');
        }

    }
}