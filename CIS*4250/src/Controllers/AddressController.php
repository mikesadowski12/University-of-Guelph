<?php
namespace WellCat\Controllers;

use PDO;
use Silex\Application;
use Symfony\Component\HttpFoundation\Request;
use WellCat\JsonResponse;

class AddressController
{
    protected $app;

    public function __construct(Application $app)
    {
        $this->app = $app;
    }

    /**
     * Gets list of countries 
     */
    public function Countries()
    {
        $sql ='SELECT countryid AS id, countryname AS name FROM country';
        $stmt= $this->app['db']->prepare($sql);
        $stmt->execute();

        $result = $stmt->fetchAll(\PDO::FETCH_ASSOC);

        if ($result) {
            $body = array(
                'success' => true,
                'countries' => $result
            );
            return new JsonResponse($body, 200);
        }
        else {
            $body = array( 
                'success' => false,
                'error' => 'no results for that id'   
            );
            return new JsonResponse($body, 404);
        }
    }

    /**
     * Gets list of locations based on given country
     * @param [int]  $country a countryid from the countries list
     */
    public function Locations($country)
    {

        $sql ='SELECT locationid AS id, locationname AS name FROM location WHERE countryid = :countryID';
        $stmt= $this->app['db']->prepare($sql);
        $stmt->execute(array( ':countryID' => $country));

        $result = $stmt->fetchAll(\PDO::FETCH_ASSOC);

        if ($result) {
            $body = array( 
                'success' => true,
                'locations' => $result
            );
            return new JsonResponse($body, 200);
        }
        else {
            $body = array( 
                'success' => false,
                'error' => 'no results for that id' 
            );
            return new JsonResponse($body, 404);
        }
    }
}
