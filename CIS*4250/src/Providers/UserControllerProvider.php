<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ControllerCollection;
use Silex\ControllerProviderInterface;
use Silex\ServiceProviderInterface;
use WellCat\Controllers\UserController;
use WellCat\JsonResponse;

class UserControllerProvider implements ControllerProviderInterface, ServiceProviderInterface
{

    /**
     * Registers
     */
    public function register(Application $app)
    {
        $app['api.user'] = $app->share(function () use ($app) {
            return new UserController($app);
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
            ->get('/authenticate', 'api.user:Authenticate')
            ->before($userAuthenticate)
        ;

        $controllers
            ->post('/register', 'api.user:Register')
        ;

        $controllers
            ->post('/login', 'api.user:Login')
        ;

        $controllers
            ->put('/changePassword', 'api.user:ChangePassword')
            ->before($userAuthenticate)
        ;

        $controllers
            ->put('/update', 'api.user:UpdateUsr')
            ->before($userAuthenticate)
        ;

        $controllers
            ->get('/view', 'api.user:ViewUsr')
            ->before($userAuthenticate)
        ;

        $controllers
            ->post('/logout', 'api.user:Logout')
        ;

        return $controllers;
    }
}
