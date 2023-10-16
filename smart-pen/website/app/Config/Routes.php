<?php

namespace Config;

// Create a new instance of our RouteCollection class.
$routes = Services::routes();

// Load the system's routing file first, so that the app and ENVIRONMENT
// can override as needed.
if (file_exists(SYSTEMPATH . 'Config/Routes.php')) {
    require SYSTEMPATH . 'Config/Routes.php';
}

/*
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
$routes->get('/detail/(:any)', 'Home::detail/$1');
$routes->get('/edit_pwd/(:any)', 'Home::edit/$1');
$routes->post('/update_pwd/(:any)', 'Home::ubah/$1');

$routes->post('/login', 'Login::login');
$routes->get('/login', 'Login::index');
$routes->get('/logout', 'Login::logout');

$routes->get('/finger/(:any)', 'FingerApi::finger/$1');

$routes->get('/record', 'Record::index');
$routes->get('/add_record', 'Record::add');
$routes->get('/edit_record/(:any)', 'Record::edit/$1');
$routes->post('/save_record', 'Record::tambah');
$routes->post('/update_record/(:any)', 'Record::ubah/$1');
$routes->delete('/record/(:any)', 'Record::delete/$1');

$routes->get('/dokter', 'Dokter::index');
$routes->get('/add_dokter', 'Dokter::add');
$routes->get('/edit_dokter/(:any)', 'Dokter::edit/$1');
$routes->post('/save_dokter', 'Dokter::tambah');
$routes->post('/update_dokter/(:any)', 'Dokter::ubah/$1');
$routes->delete('/dokter/(:any)', 'Dokter::delete/$1');


$routes->get('/pasien', 'Pasien::index');
$routes->get('/add_pasien', 'Pasien::add');
$routes->get('/edit_pasien/(:any)', 'Pasien::edit/$1');
$routes->post('/save_pasien', 'Pasien::tambah');
$routes->post('/update_pasien/(:any)', 'Pasien::ubah/$1');
$routes->delete('/pasien/(:any)', 'Pasien::delete/$1');

$routes->get('/device', 'Device::index');
$routes->get('/add_device', 'Device::add');
$routes->get('/edit_device/(:any)', 'Device::edit/$1');
$routes->post('/save_device', 'Device::tambah');
$routes->post('/update_device/(:any)', 'Device::ubah/$1');
$routes->delete('/device/(:any)', 'Device::delete/$1');

// $routes->get('/show', 'Home::showReal');

// $routes->get('/finger/(:any)', 'FingerApi::finger/$1');

// $routes->post('/login', 'Login::login');
// $routes->get('/login', 'Login::index');
// $routes->get('/logout', 'Login::logout');

// $routes->get('/data_siswa', 'DataSiswa::index');
// $routes->get('/detailsiswa', 'DataSiswa::detailSiswa');
// $routes->get('/addsiswa', 'DataSiswa::addSiswa');
// $routes->get('/editsiswa/(:any)', 'DataSiswa::editSiswa/$1');
// $routes->post('/tambah_siswa', 'DataSiswa::tambah');
// $routes->post('/edit_siswa/(:any)', 'DataSiswa::update/$1');
// $routes->delete('/data_siswa/(:any)', 'DataSiswa::delete/$1');

// $routes->get('/data_kelas', 'DataKelas::index');
// $routes->get('/addkelas', 'DataKelas::addKelas');
// $routes->get('/editkelas/(:any)', 'DataKelas::editKelas/$1');
// $routes->post('/tambah_kelas', 'DataKelas::tambah');
// $routes->post('/edit_kelas/(:any)', 'DataKelas::update/$1');
// $routes->delete('/data_kelas/(:any)', 'DataKelas::delete/$1');


// $routes->get('/editjadwal/(:any)', 'Jadwal::editJadwal/$1');
// $routes->post('/editjadwal/(:any)', 'Jadwal::update/$1');

// $routes->get('/adduser', 'DataUsers::addUser');
// $routes->get('/editpwd/(:any)', 'DataUsers::editPwd/$1');
// $routes->get('/resetpwd/(:any)', 'DataUsers::resetPwd/$1');
// $routes->get('/reset/(:any)', 'DataUsers::reset/$1');
// $routes->delete('/datauser/(:any)', 'DataUsers::delete/$1');
// $routes->post('/register', 'DataUsers::register');
// $routes->post('/ubahpwd/(:any)', 'DataUsers::ubahPwd/$1');

// $routes->post('/report', 'ExelReport::exelAbsesi');


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
if (file_exists(APPPATH . 'Config/' . ENVIRONMENT . '/Routes.php')) {
    require APPPATH . 'Config/' . ENVIRONMENT . '/Routes.php';
}
