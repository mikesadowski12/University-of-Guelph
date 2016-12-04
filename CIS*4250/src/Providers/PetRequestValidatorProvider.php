<?php
namespace WellCat\Providers;

use Silex\Application;
use Silex\ServiceProviderInterface;
use WellCat\Validators\PetRequestValidator;

class PetRequestValidatorProvider implements ServiceProviderInterface
{
    public function register(Application $app)
    {
        $app['api.petrequestvalidator'] = $app->share(function () use ($app) {
            return new PetRequestValidator($app);
        });
    }

    public function boot(Application $app)
    {

    }
}
