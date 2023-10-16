<?php

namespace App\Controllers;

use App\Models\PasienModel;
use App\Models\DeviceModel;

class Pasien extends BaseController
{

    public function __construct()
    {
        $this->statusLogin();
        $this->aksesDokter(session()->get("user_akses"));
        $this->pasienModel = new PasienModel; 
        $this->deviceModel = new DeviceModel; 
    }

    public function index()
    {            
        $data = [
            'title' => 'Data Pasien',  
            'datas' => $this->pasienModel->findAll(),          
        ];
        return view('pasien/index',$data);
    }

    public function add()
    {            
        $data = [
            'title' => 'Tambah Data',   
            'validation' => \Config\Services::validation(), 
            'title' => 'Tambah Data',         
        ];
        return view('pasien/add',$data);
    }

    public function tambah(){
        
        if (!$this->validate([
            'id_finger' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'no_identitas' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'nama_pasien' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'alamat' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'jenis_kelamin' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'tempat_lahir' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'tanggal_lahir' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ]
        ])) {

            return redirect()->to(base_url('add_pasien'))->withInput();
        }
        
        $device = $this->deviceModel->getByID(session()->get("serial_device"));
        $startID = $device["start_id"];
        $endID = $device["end_id"];
        $id_finger = $this->request->getVar('id_finger');

        if($id_finger < $startID || $id_finger > $endID){            
            session()->setFlashdata('pesan', 'Input ID finger dengan benar.! ('.$startID.' - '.$endID.')');
            return redirect()->to(base_url('add_pasien'))->withInput();
        }
     
        $data = [
            'id_finger'     => $this->request->getVar('id_finger'),
            'no_identitas'  => $this->request->getVar('no_identitas'),
            'nama_pasien'   => $this->request->getVar('nama_pasien'),
            'alamat'        => $this->request->getVar('alamat'),
            'jenis_kelamin' => $this->request->getVar('jenis_kelamin'),
            'golongan_darah'=> $this->request->getVar('golongan_darah'),
            'tempat_lahir'  => $this->request->getVar('tempat_lahir'),
            'tanggal_lahir' => $this->request->getVar('tanggal_lahir'),
            'agama'         => $this->request->getVar('agama'),
            'no_telepon'    => $this->request->getVar('no_telepon'),
        ];

        //dd($data);

        $this->pasienModel->insert($data);

        session()->setFlashdata('pesan', 'Data berhasil di tambahkan');

        return redirect()->to(base_url('pasien'));
    }

    public function edit($id_finger)
    {            
        $data = [
            'title' => 'Ubah Data', 
            'data'  => $this->pasienModel->getByID($id_finger),   
            'validation' => \Config\Services::validation(),        
        ];
        return view('pasien/edit',$data);
    }

    public function ubah($id_finger){

        if (!$this->validate([
            
            'no_identitas' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'nama_pasien' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'alamat' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'jenis_kelamin' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'tempat_lahir' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'tanggal_lahir' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ]
        ])) {

            return redirect()->to(base_url('edit_pasien/'.$id_finger))->withInput();
        }     
     
        $data = [
            'id_finger'     => $id_finger,
            'no_identitas'  => $this->request->getVar('no_identitas'),
            'nama_pasien'   => $this->request->getVar('nama_pasien'),
            'alamat'        => $this->request->getVar('alamat'),
            'jenis_kelamin' => $this->request->getVar('jenis_kelamin'),
            'golongan_darah'=> $this->request->getVar('golongan_darah'),
            'tempat_lahir'  => $this->request->getVar('tempat_lahir'),
            'tanggal_lahir' => $this->request->getVar('tanggal_lahir'),
            'agama'         => $this->request->getVar('agama'),
            'no_telepon'    => $this->request->getVar('no_telepon'),
        ];

        //dd($data);

        $this->pasienModel->save($data);

        session()->setFlashdata('pesan', 'Data berhasil di Ubah');

        return redirect()->to(base_url('pasien'));
    }



    public function delete($id_finger = false)
    {
        $this->pasienModel->delete($id_finger);
        session()->setFlashdata('pesan', 'Data berhasil di hapus');
        return redirect()->to(base_url('pasien'));
    }
}
