<?php

namespace WellCat\Providers;

use Silex\Application;
use Silex\ControllerCollection;
use Silex\ControllerProviderInterface;
use Silex\ServiceProviderInterface;
use WellCat\Controllers\PetController;
use WellCat\JsonResponse;

class PetControllerProvider  implements ControllerProviderInterface, ServiceProviderInterface
{
    /**
     * Registers
     */
    public function register(Application $app)
    {
        $app['api.pet'] = $app->share(function () use ($app) {
            return new PetController($app);
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
         $userAuthenticate = function () use ($app) {
            if ($app['api.auth']->Authenticated() == false) {
                $body = array(
                    'success' => 'false',
                    'error' => 'User not authenticated'
                );
                return new JsonResponse($body, 401);
            }
        };

        $controllers = $app['controllers_factory'];

        $controllers
            ->post('/create', 'api.pet:Create')
            ->before($userAuthenticate)
        ;

        $controllers
            ->post('/accessibility', 'api.pet:SetAccessibility')
            ->before($userAuthenticate)
        ;

        $controllers
            ->delete('/accessibility', 'api.pet:RemoveAccessibility')
            ->before($userAuthenticate)
        ;

        $controllers
            ->get('/sharedPets', 'api.pet:GetAccessibilities')
            ->before($userAuthenticate)
        ;


        $controllers
            ->get('/view/{petID}', 'api.pet:GetPet')
            ->before($userAuthenticate)
        ;

        $controllers
            ->get('/pets', 'api.pet:GetAllPets')
            ->before($userAuthenticate)
        ;

        $controllers
            ->put('/update', 'api.pet:UpdatePet')
            ->before($userAuthenticate)
        ;

        $controllers
            ->delete('/remove', 'api.pet:RemovePet')
            ->before($userAuthenticate)
        ;

        return $controllers;
    }
}
