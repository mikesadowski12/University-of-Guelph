<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ServiceProviderInterface;
use PDO;
use WellCat\Services\AddressService;

class AddressServiceProvider implements ServiceProviderInterface
{
    public function register(Application $app)
    {
        $app['api.address'] = $app->share(function () use ($app) {
            return new AddressService($app);
        });
    }

    public function boot(Application $app)
    {

    }
}
