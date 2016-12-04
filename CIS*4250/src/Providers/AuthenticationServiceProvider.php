<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ServiceProviderInterface;
use PDO;
use WellCat\Services\AuthenticationService;

class AuthenticationServiceProvider implements ServiceProviderInterface
{
    public function register(Application $app)
    {
        $app['api.auth'] = $app->share(function () use ($app) {
            return new AuthenticationService($app, $app['config']['crypto']['salt']);
        });
    }

    public function boot(Application $app)
    {

    }
}
