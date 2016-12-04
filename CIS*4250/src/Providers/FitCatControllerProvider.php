<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ControllerCollection;
use Silex\ControllerProviderInterface;
use Silex\ServiceProviderInterface;
use WellCat\Controllers\FitCatController;
use WellCat\JsonResponse;

class FitCatControllerProvider implements ControllerProviderInterface, ServiceProviderInterface
{

    /**
     * Registers
     */
    public function register(Application $app)
    {
        $app['api.fitcat'] = $app->share(function () use ($app) {
            return new FitCatController($app);
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
            ->post('/weight', 'api.fitcat:Weight')
            ->before($userAuthenticate)
        ;

        $controllers
            ->post('/steps', 'api.fitcat:Steps')
            ->before($userAuthenticate)
        ;

        $controllers
            ->post('/water', 'api.fitcat:Water')
            ->before($userAuthenticate)
        ;
        
        $controllers
            ->post('/food', 'api.fitcat:Food')
            ->before($userAuthenticate)
        ;

        $controllers
            ->get('/pets', 'api.fitcat:Pets')
            ->before($userAuthenticate)
        ;

        $controllers
            ->get('/view/{petID}', 'api.fitcat:View')
            ->before($userAuthenticate)
        ;

        $controllers
            ->post('/register', 'api.fitcat:Register')
            ->before($userAuthenticate)
        ;

        $controllers
            ->post('/deregister', 'api.fitcat:DeRegister')
            ->before($userAuthenticate)
        ;

    	//$controllers
        //    ->get('/view/{petid}/{date}', 'api.fitcat:View')
        //;
        
	return $controllers;
    }
}
