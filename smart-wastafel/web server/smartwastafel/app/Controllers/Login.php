<?php

namespace App\Controllers;

use App\Controllers\BaseController;

use App\Models\LoginModel;

use function PHPSTORM_META\type;

class Login extends BaseController
{

    public function __construct()
    {
         $this->loginModel = new LoginModel();
    }

    public function index()
    {
        $data = [
            "title" => "Smart Wastafel | Login",   
        ];
        return view('login', $data);
    }

    public function auth()
    {
        $user      = $this->request->getVar('username');
        $password   = $this->request->getVar('password');

        $cek_login = $this->loginModel->cek_login($user);

        if($cek_login){
            if(password_verify($password, $cek_login['password']))
            {
                session()->set('username',$user);
                return redirect()->to(base_url().'/');
            } else {
                session()->setFlashdata('pesan', 'username atau password salah');
                return redirect()->to(base_url().'/login');
            }
        }else{
            session()->setFlashdata('pesan', 'username atau password salah');
            return redirect()->to(base_url().'/login');
        }
    }

}
