<?php

namespace WellCat\Services;

use Silex\Application;

class AnimalService
{
    protected $app;

    public function __construct(Application $app)
    {
        $this->app = $app;
    }

    public function CheckBreedExists($breedID)
    {
        if (!$breedID || !is_numeric($breedID)) {
            return false;
        }

        $sql = 'SELECT NULL FROM breed WHERE breedid = :breedID';

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
          ':breedID' => $breedID
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        if ($result) {
            return true;
        } else {
            return false;
        }
    }

    public function CheckAnimalExists($animalID)
    {
        if (!$animalID || !is_numeric($animalID)) {
            return false;
        }

        $sql = 'SELECT NULL FROM animal WHERE animaltypeid = :animalID';

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
          ':animalID' => $animalID
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        if ($result) {
            return true;
        } else {
            return false;
        }
    }

    public function CheckGenderExists($genderID)
    {
        if (!$genderID || !is_numeric($genderID)) {
            return false;
        }

        $sql = 'SELECT NULL FROM gender WHERE genderid = :genderID';

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
          ':genderID' => $genderID
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        if ($result) {
            return true;
        } else {
            return false;
        }
    }
}
