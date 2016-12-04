<?php

namespace WellCat\Services;

use Silex\Application;

class DatabaseTypesService
{
    protected $app;

    public function __construct(Application $app)
    {
        $this->app = $app;
    }

    public function IsValidPetAccessibilityValue($petAccessibility)
    {
        $sql = 'SELECT * FROM unnest(enum_range(NULL::pet_accessibility)) AS value';

        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute();

        $result = $stmt->fetchAll(\PDO::FETCH_ASSOC);

        return in_array(array('value' => $petAccessibility), $result);
    }
}
