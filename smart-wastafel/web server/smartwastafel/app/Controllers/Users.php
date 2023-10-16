<?php

namespace App\Controllers;

use App\Controllers\BaseController;

use App\Models\LoginModel;

use function PHPSTORM_META\type;

class Users extends BaseController
{

    public function __construct()
    {
         $this->loginModel = new LoginModel();
    }

    public function index()
    {
        if(!session()->has('username')){
			return redirect()->to(base_url().'/login');
		}
        $data = [
            "title" => "Smart Wastafel | Data Users",
            "data_users" => $this->loginModel->getUsers()->paginate(6,'users'),
            "pager" => $this->loginModel->pager
        ];
        return view('users', $data);
    }

    public function delete($id = false)
    {
        $this->loginModel->delete($id);
        session()->setFlashdata('pesan', 'Data berhasil di hapus');
        return redirect()->to(base_url().'/users');
    }

    public function create()
    {
        $data = [
            "title"      => "Smart Wastafel | Create New User",
            'validation' => \Config\Services::validation(),
        ];
        return view('register', $data);
    }

    public function save()
    {
        if (!$this->validate([
            'name' => [
                'rules' => 'required',
                'errors' => [
                    'required' => 'Nama harus di isi'
                ]
            ],
            'username' => [
                'rules' => 'required|is_unique[users.username]',
                'errors' => [
                    'required' => 'Username harus di isi',
                    'is_unique' => 'Username sudah terdaftar'
                ]
            ],
            'password' => [
                'rules' => 'required',
                'errors' => [
                    'required' => 'Password harus di isi'
                ]
            ],
        ])) {
            return redirect()->to(base_url().'/users/create')->withInput();
        }

        $password   = $this->request->getVar('password');
        $password_hash = password_hash($password, PASSWORD_BCRYPT);

        $this->loginModel->save([
            'name'       => $this->request->getVar('name'),
            'username'   => $this->request->getVar('username'),
            'password'   => $password_hash,
        ]);

        session()->setFlashdata('pesan', 'Data berhasil di tambahkan');

        return redirect()->to(base_url().'/users');
    }


    //--------------------------------------------------------------------

}
