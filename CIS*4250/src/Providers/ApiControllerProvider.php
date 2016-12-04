<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ControllerCollection;
use Silex\ControllerProviderInterface;
use Silex\ServiceProviderInterface;
use WellCat\Controllers\ApiController;

class ApiControllerProvider implements ControllerProviderInterface, ServiceProviderInterface
{

    /**
     * Registers
     */
    public function register(Application $app)
    {
        $app['api.controller'] = $app->share(function () use ($app) {
            return new ApiController($app);
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
            ->get('/', 'api.controller:EndPoints')
        ;

        return $controllers;
    }
}
