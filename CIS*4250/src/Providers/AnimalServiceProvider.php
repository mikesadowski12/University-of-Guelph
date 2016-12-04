<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ServiceProviderInterface;
use PDO;
use WellCat\Services\AnimalService;

class AnimalServiceProvider implements ServiceProviderInterface
{
    public function register(Application $app)
    {
        $app['api.animalservice'] = $app->share(function () use ($app) {
            return new AnimalService($app);
        });
    }

    public function boot(Application $app)
    {

    }
}
