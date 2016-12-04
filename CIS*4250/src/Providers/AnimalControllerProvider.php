<?php

namespace WellCat\Providers;

use Silex\Application;
use Silex\ControllerCollection;
use Silex\ControllerProviderInterface;
use Silex\ServiceProviderInterface;
use WellCat\Controllers\AnimalController;
use WellCat\JsonResponse;

class AnimalControllerProvider  implements ControllerProviderInterface, ServiceProviderInterface
{
    /**
     * Registers
     */
    public function register(Application $app)
    {
        $app['api.animal'] = $app->share(function () use ($app) {
            return new AnimalController($app);
        });
    }

    public function boot(Application $app)
    {

    }

    /**
     * Returns routes to connect to the given application.
     *
     * @param Application $app An Application instance
     * @return ControllerCollection A ControllerCollection instance
     */
    public function connect(Application $app)
    {
        $controllers = $app['controllers_factory'];

        $controllers
            ->get('/animals', 'api.animal:GetAnimals')
        ;

        $controllers
            ->get('/{animalId}/breeds', 'api.animal:GetBreedsByAnimalId')
        ;

        $controllers
            ->get('/genders', 'api.animal:GetGenders')
        ;

        return $controllers;
    }
}
