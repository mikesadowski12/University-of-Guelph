<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ControllerCollection;
use Silex\ControllerProviderInterface;
use Silex\ServiceProviderInterface;
use WellCat\Controllers\AdminPMController;
use WellCat\JsonResponse;

class AdminPMControllerProvider implements ControllerProviderInterface, ServiceProviderInterface
{

    /**
     * Registers
     */
    public function register(Application $app)
    {
        $app['api.adminPM'] = $app->share(function () use ($app) {
            return new AdminPMController($app);
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
            if ($app['api.auth']->AuthenticateAdmin('practicemanagement') == false) {
                $body = array(
                    'success' => 'false',
                    'error' => 'You do not have access to do this'
                );
                return new JsonResponse($body, 403);
            }
        };

        $controllers = $app['controllers_factory'];

        $controllers
            ->get('/authenticate', 'api.adminPM:Authenticate')
            ->before($adminAuthenticate)
            ->before($userAuthenticate)
        ;

        $controllers
            ->post('/create', 'api.adminPM:Create')
            ->before($adminAuthenticate)
            ->before($userAuthenticate)
        ;

        $controllers
            ->put('/update', 'api.adminPM:UpdatePet')
            ->before($adminAuthenticate)
            ->before($userAuthenticate)
        ;

        return $controllers;
    }
}
