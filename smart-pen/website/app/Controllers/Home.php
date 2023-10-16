<?php

namespace App\Controllers;

use App\Models\RecordModel;
use App\Models\DokterModel;
use App\Models\LogModel;

class Home extends BaseController
{

    public function __construct()
    {
        $this->statusLogin();

        $this->aksesDokter(session()->get("user_akses"));

        $this->recordModel = new RecordModel;
        $this->logModel = new LogModel;
        $this->dokterModel = new DokterModel;
    }

    public function index()
    {           
        $data =  $this->logModel->getFirst();        
        $id_finger = $data['id_finger'];

        if($data['message']== 0){
            session()->setFlashdata('pesan', 'Pasien belum terdaftar!');
            $data = [
                'title' => 'Home', 
                'datas' => $this->logModel->getJoin($id_finger),           
            ];  
            return view('home/index',$data);
        }else if($data['message']== 1){
            session()->setFlashdata('pesan', 'Data Rekam Medis tidak ditemukan!');
            $data = [
                'title' => 'Home', 
                'datas' => $this->logModel->getJoin($id_finger),           
            ];  
            return view('home/index',$data);
        }else{        
            $data = [
                'title' => 'Home', 
                'datas' => $this->logModel->getJoin($id_finger),           
            ];        
            return view('home/index',$data);
        }
    }

    public function detail($no_rm)
    {           
        $data = [
          'title' => 'Rekam Medis', 
          'data' => $this->logModel->getRm($no_rm),           
        ];  
        return view('home/detail',$data);        
    }

    public function edit($kode)
    {            
        $data = [
            'title' => 'Ubah Password',  
            'validation' => \Config\Services::validation(),   
            'data' => $kode           
        ];
        return view('home/edit_pwd',$data);
    }

    public function ubah($kode){
        
        if (!$this->validate([
            'old_password' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'password' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'confir_password' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ]
        ])) {
            session()->setFlashdata('pesan', 'Input password harus di isi!');
            return redirect()->to(base_url("edit_pwd/".$kode))->withInput();
        }  
        
        $data = $this->dokterModel->getByID($kode);
        $old_password = $this->request->getVar('old_password');
        $new_password = $this->request->getVar('password');
        $confir_password = $this->request->getVar('confir_password');

        if(!password_verify($old_password, $data['password'])){
            session()->setFlashdata('pesan', 'Password tidak cocok!');
            return redirect()->to(base_url("edit_pwd/".$kode))->withInput();
        }else if($new_password != $confir_password){
            session()->setFlashdata('pesan', 'Konfirmasi password tidak cocok!');
            return redirect()->to(base_url("edit_pwd/".$kode))->withInput();
        }else{

         $data = [
            'kode_dokter'     => $kode,           
            'password'        => password_hash($new_password, PASSWORD_BCRYPT),            
            ];

         $this->dokterModel->save($data);

         session()->setFlashdata('pesan', 'Data Password berhasil di ubah');

         return redirect()->to(base_url('/'));
        }
    }
}
