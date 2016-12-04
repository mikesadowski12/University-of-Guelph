<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ControllerCollection;
use Silex\ControllerProviderInterface;
use Silex\ServiceProviderInterface;
use WellCat\Controllers\AddressController;
use WellCat\JsonResponse;

class AddressControllerProvider implements ControllerProviderInterface, ServiceProviderInterface
{

    /**
     * Registers
     */
    public function register(Application $app)
    {
        $app['api.addr'] = $app->share(function () use ($app) {
            return new AddressController($app);
        });
    }

    public function boot(Application $app)
    {

    }

    /**
     * Returns routes to connect to the given application.
     *
     * @param Application $app An Application instance
     *
     * @return ControllerCollection A ControllerCollection instance
     */
    public function connect(Application $app)
    {
        $controllers = $app['controllers_factory'];

        $controllers
            ->get('/countries', 'api.addr:Countries')
        ;

        $controllers
            ->get('/{country}/locations', 'api.addr:Locations')
        ;

        return $controllers;
    }
}   
