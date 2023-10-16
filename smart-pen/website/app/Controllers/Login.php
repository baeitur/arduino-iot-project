<?php

namespace App\Controllers;

use App\Models\DokterModel;

class Login extends BaseController
{

    public function __construct()
    {
        $this->dokterModel = new DokterModel;
    }

    public function index()
    {
        return view('login/login');
    }

    public function logout()
    {
        $remove_session = ['kode_dokter', 'nama_dokter'];
        session()->remove($remove_session);
        return redirect()->to(base_url('/login'));
    }

    public function login()
    {
        
        $user      = $this->request->getVar('kode_dokter');
        $password   = $this->request->getVar('password');

        $cek_login = $this->dokterModel->cek_login($user);
        if($user == 'admin' && $password == '12345678'){
            $start_session = [
                'kode_dokter' => 'admin sistem',
                'nama_dokter' => 'admin sistem',
                'user_akses' => 'admin'
            ];
            session()->set($start_session);
            return redirect()->to(base_url('/dokter'));
        }
        else if (!$cek_login) {
            session()->setFlashdata('pesan', 'Kode dokter tidak di temukan!');
            return redirect()->to(base_url('login'));
        }

        if (password_verify($password, $cek_login['password'])) {
            $start_session = [
                'kode_dokter' => $cek_login['kode_dokter'],
                'nama_dokter' => $cek_login['nama_dokter'],
                'user_akses'  => 'dokter',
                'serial_device' => $cek_login['serial_device'],                
                'foto'        => $cek_login['foto'],
            ]; 
            session()->set($start_session);
            return redirect()->to(base_url('/'));
        } else {
            session()->setFlashdata('pesan', 'Password tidak cocok!');
            return redirect()->to(base_url('/login'));
        }
    }
}
