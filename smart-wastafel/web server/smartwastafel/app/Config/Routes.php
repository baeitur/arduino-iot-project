<?php

namespace Config;

// Create a new instance of our RouteCollection class.
$routes = Services::routes();

// Load the system's routing file first, so that the app and ENVIRONMENT
// can override as needed.
if (file_exists(SYSTEMPATH . 'Config/Routes.php'))
{
	require SYSTEMPATH . 'Config/Routes.php';
}

/**
 * --------------------------------------------------------------------
 * Router Setup
 * --------------------------------------------------------------------
 */
$routes->setDefaultNamespace('App\Controllers');
$routes->setDefaultController('Home');
$routes->setDefaultMethod('index');
$routes->setTranslateURIDashes(false);
$routes->set404Override();
$routes->setAutoRoute(true);

/*
 * --------------------------------------------------------------------
 * Route Definitions
 * --------------------------------------------------------------------
 */

// We get a performance increase by specifying the default
// route since we don't have to scan directories.
$routes->get('/', 'Home::index');
$routes->get('/logout', 'Home::logout');

$routes->get('/login', 'Login::index');
$routes->get('/login/auth', 'Login::auth');

$routes->get('/battery', 'Battery::index');
$routes->get('/battery/(:any)', 'BatteryApi::create/$1'); //add
$routes->delete('/battery/(:any)', 'Battery::delete/$1'); //delete

$routes->get('/pengguna', 'Pengguna::index');
$routes->get('/pengguna/video/(:any)', 'PenggunaApi::update/$1'); //update video
$routes->get('/pengguna/(:any)/(:any)', 'PenggunaApi::create/$1/$2'); //add
$routes->delete('/pengguna/(:any)/(:any)', 'Pengguna::delete/$1/$2'); //delete

$routes->get('/download/(:any)', 'Download::download/$1'); //delete

$routes->get('/users', 'Users::index');
//$routes->get('/pengguna/(:any)/(:any)', 'PenggunaApi::create/$1/$2'); //add
$routes->delete('/users/(:any)', 'Users::delete/$1'); //delete

/*
 * --------------------------------------------------------------------
 * Additional Routing
 * --------------------------------------------------------------------
 *
 * There will often be times that you need additional routing and you
 * need it to be able to override any defaults in this file. Environment
 * based routes is one such time. require() additional route files here
 * to make that happen.
 *
 * You will have access to the $routes object within that file without
 * needing to reload it.
 */
if (file_exists(APPPATH . 'Config/' . ENVIRONMENT . '/Routes.php'))
{
	require APPPATH . 'Config/' . ENVIRONMENT . '/Routes.php';
}
