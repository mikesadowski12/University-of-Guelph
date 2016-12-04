<?php

namespace WellCat\Controllers;

use WellCat\JsonResponse;

class AnimalController
{
    protected $app;

    public function __construct(\Silex\Application $app)
    {
        $this->app = $app;
        $this->app['session']->start();
    }

    /**
     * gets a list of animals that are known
     */
    public function GetAnimals()
    {
        // Get animals from database
        $sql = 'SELECT animaltypeid AS id, name FROM animal';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute();

        $result = $stmt->fetchAll(\PDO::FETCH_ASSOC);


        if ($result) {
            $body = array(
                'success' => true,
                'animals' => $result
            );

            return new JsonResponse($body, 200);
        } 
        else {
            $body = array(
                'success' => false,
                'error' => "Unable to get animals."
            );

            return new JsonResponse ($body, 500);
        }
    }

    /**
     * Gets listof breeds based on a given animal
     * @param [int] $animalId a animalID that is gotten from the list of animals
     */
    public function GetBreedsByAnimalId($animalId)
    {
        if (!$animalId) {
            return JsonResponse::missingParam('animalId');
        }
        elseif (!is_numeric($animalId)) {
            return JsonResponse::userError('Invalid animal type id '.$animalId);
        }

        // Get breeds from database
        $sql = 'SELECT breedId as id, name FROM breed WHERE animaltypeid = :animaltypeid';
        $stmt = $this->app['db']->prepare($sql);
        $success = $stmt->execute(array(
            ':animaltypeid' => $animalId
        ));

        $result = $stmt->fetchAll(\PDO::FETCH_ASSOC);

        if ($result) {
            $body = array(
                'success' => true,
                'breeds' => $result
            );

            return new JsonResponse($body, 200);
        } 
        else {
            $body = array(
                'success' => false,
                'error' => "Unable to retrieve breeds."
            );

            return new JsonResponse ($body, 500);
        }
    }

    /**
     * Gets a list of known genders
     */
    public function GetGenders()
    {
        // Get genders from database
        $sql = 'SELECT genderid AS id, name FROM gender';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute();

        $result = $stmt->fetchAll(\PDO::FETCH_ASSOC);


        if ($result) {
            $body = array(
                'success' => true,
                'genders' => $result
            );

            return new JsonResponse($body, 200);
        } 
        else {
            $body = array(
                'success' => false,
                'error' => "Unable to get animals."
            );

            return new JsonResponse ($body, 500);
        }
    }
}
