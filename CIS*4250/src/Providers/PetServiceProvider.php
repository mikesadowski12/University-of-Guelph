<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ServiceProviderInterface;
use PDO;
use WellCat\Services\PetService;

class PetServiceProvider implements ServiceProviderInterface
{
    public function register(Application $app)
    {
        $app['api.petservice'] = $app->share(function () use ($app) {
            return new PetService($app);
        });
    }

    public function boot(Application $app)
    {

    }
}