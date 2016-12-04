<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ServiceProviderInterface;
use PDO;
use WellCat\Services\DatabaseTypesService;

class DatabaseTypesServiceProvider implements ServiceProviderInterface
{
    public function register(Application $app)
    {
        $app['api.dbtypes'] = $app->share(function () use ($app) {
            return new DatabaseTypesService($app);
        });
    }

    public function boot(Application $app)
    {

    }
}
