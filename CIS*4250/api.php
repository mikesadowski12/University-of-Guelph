<?php

//FIXME: remove the next 3 lines in production
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(-1);

header('Access-Control-Allow-Origin: http://localhost:8080');
header('Access-Control-Allow-Methods: GET,PUT,DELETE,POST');
require_once __DIR__.'/vendor/autoload.php';

use WellCat\Providers\ApiControllerProvider;
use WellCat\Providers\AdminUserControllerProvider;
use WellCat\Providers\UserControllerProvider;
use WellCat\Providers\PetControllerProvider;
use WellCat\Providers\AddressControllerProvider;
use WellCat\Providers\AnimalControllerProvider;

use WellCat\Providers\AdminPMControllerProvider;
use WellCat\Providers\FitCatControllerProvider;

$app = new Silex\Application();
$app['env'] = 'dev';
require_once __DIR__.'/config/configFile.php';
require_once __DIR__.'/src/wellCat.php';

$apiConProv = new ApiControllerProvider();
$app->register($apiConProv);
$app->mount('/', $apiConProv);

$adminUserConProv = new AdminUserControllerProvider();
$app->register($adminUserConProv);
$app->mount('/user', $adminUserConProv);

$userConProv = new UserControllerProvider();
$app->register($userConProv);
$app->mount('/user', $userConProv);

$petConProv = new PetControllerProvider();
$app->register($petConProv);
$app->mount('/pet', $petConProv);

$addrConProv = new AddressControllerProvider();
$app->register($addrConProv);
$app->mount('/address', $addrConProv);

$animalConProv = new AnimalControllerProvider();
$app->register($animalConProv);
$app->mount('/animal', $animalConProv);

$adminPMConProv = new AdminPMControllerProvider();
$app->register($adminPMConProv);
$app->mount('/PM', $adminPMConProv);

$fitcatConProv = new FitCatControllerProvider();
$app->register($fitcatConProv);
$app->mount('/fitcat', $fitcatConProv);

$app->run();
