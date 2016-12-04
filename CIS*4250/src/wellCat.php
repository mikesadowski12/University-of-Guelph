<?php

$env = $app['env'];

/*
 * Register
 */
$app->register(new Silex\Provider\ServiceControllerServiceProvider());
$app->register(new Silex\Provider\SessionServiceProvider());

/*
 * Error handler
 */
$app->error(function (\Exception $e, $code) use ($app) {
    echo $e->getMessage();
    exit;
});

/*
 *DB connection
 */
$app->register(new \WellCat\Providers\DatabaseServiceProvider());
$app['db']->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

// Services
$app->register(new \WellCat\Providers\AddressServiceProvider());
$app->register(new \WellCat\Providers\AuthenticationServiceProvider());
$app->register(new \WellCat\Providers\AnimalServiceProvider());
$app->register(new \WellCat\Providers\DatabaseTypesServiceProvider());
$app->register(new \WellCat\Providers\PetServiceProvider());

// Validators
$app->register(new \WellCat\Providers\PetRequestValidatorProvider());

//Convert json bodies to objects
$app->before(function (\Symfony\Component\HttpFoundation\Request $request) {
    if (0 === strpos($request->headers->get('Content-Type'), 'application/json')) {
        $data = json_decode($request->getContent(), true);
        $request->request->replace(is_array($data) ? $data : array());
    }
});
