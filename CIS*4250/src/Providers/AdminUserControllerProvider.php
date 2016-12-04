<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ControllerCollection;
use Silex\ControllerProviderInterface;
use Silex\ServiceProviderInterface;
use WellCat\Controllers\AdminUserController;
use WellCat\JsonResponse;

class AdminUserControllerProvider implements ControllerProviderInterface, ServiceProviderInterface
{

    /**
     * Registers
     */
    public function register(Application $app)
    {
        $app['api.adminUser'] = $app->share(function () use ($app) {
            return new AdminUserController($app);
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

        $adminAuthenticate = function () use ($app) {
            if ($app['api.auth']->AuthenticateAdmin('usersearch') == false) {
                $body = array(
                    'success' => 'false',
                    'error' => 'You do not have access to do this'
                );
                return new JsonResponse($body, 403);
            }
        };

        $controllers = $app['controllers_factory'];

        $controllers
            ->get('/authenticated', 'api.adminUser:Authenticate')
            ->before($adminAuthenticate)
            ->before($userAuthenticate)
        ;

        $controllers
            ->get('/search', 'api.adminUser:Search')
            ->before($adminAuthenticate)
            ->before($userAuthenticate)
        ;

        $controllers
            ->get('/view/{userID}', 'api.adminUser:View')
            ->before($adminAuthenticate)
            ->before($userAuthenticate)
        ;

        return $controllers;
    }
}
