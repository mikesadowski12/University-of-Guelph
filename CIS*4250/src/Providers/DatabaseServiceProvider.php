<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ServiceProviderInterface;
use PDO;

class DatabaseServiceProvider implements ServiceProviderInterface
{
    public function register(Application $app)
    {
        $app['db'] = $app->share(function () use ($app) {
            $dbconfig = $app['config']['database'];
            $db = new PDO(
                'pgsql:host='.$dbconfig['host'].';dbname=' . $dbconfig['dbname'],
                $dbconfig['user'],
                $dbconfig['pass'],
                array(
                    \PDO::ATTR_PERSISTENT => true,
                    \PDO::ATTR_ERRMODE => \PDO::ERRMODE_EXCEPTION
                )
            );

            return $db;
        });
    }

    public function boot(Application $app)
    {

    }
}
