<?php

namespace App\Controllers;

use App\Models\DeviceModel;

class Device extends BaseController
{

    public function __construct()
    {
        $this->aksesAdmin(session()->get("user_akses"));
        $this->statusLogin();
        $this->deviceModel = new DeviceModel;  
    }

    public function index()
    {            
        $data = [
            'title' => 'Device', 
            'datas' => $this->deviceModel->findAll(),               
        ];
        return view('device/index',$data);
    }

    public function add()
    {            
        $data = [
            'title' => 'Tambah Data', 
            'validation' => \Config\Services::validation(),           
        ];
        return view('device/add',$data);
    }

    public function tambah(){

        if (!$this->validate([
            'serial_device' => [
                'rules' => 'required|is_unique[device.serial_device]',
                'errors' => [
                    'required' => '{field} harus di isi',
                    'is_unique' => '{field} sudah terdaftar'
                ]
            ],
            'start_id' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'end_id' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ]
        ])) {

            return redirect()->to(base_url('add_device'))->withInput();
        }
     
        $data = [
            'serial_device' => $this->request->getVar('serial_device'),
            'start_id'      => $this->request->getVar('start_id'),
            'end_id'        => $this->request->getVar('end_id'),
            'status'        => 0,
        ];

        //dd($data);

        $this->deviceModel->insert($data);

        session()->setFlashdata('pesan', 'Data berhasil di tambahkan');

        return redirect()->to(base_url('device'));
    }


    public function edit($serial)
    {            
        $data = [
            'title' => 'Ubah Data', 
            'data'  => $this->deviceModel->getByID($serial),  
            'validation' => \Config\Services::validation(),             
        ];
        return view('device/edit',$data);
    }

    public function ubah($serial){

        if (!$this->validate([
            'serial_device' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'start_id' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'end_id' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ]
        ])) {

            return redirect()->to(base_url('edit_device/'.$serial))->withInput();
        }

     
        $data = [
            'serial_device' => $this->request->getVar('serial_device'),
            'start_id'      => $this->request->getVar('start_id'),
            'end_id'        => $this->request->getVar('end_id'),
            'status'        => 0,
        ];

        //dd($data);

        $this->deviceModel->save($data);

        session()->setFlashdata('pesan', 'Data berhasil di ubah');

        return redirect()->to(base_url('device'));
    }

    public function delete($serial = false)
    {
        $this->deviceModel->delete($serial);
        session()->setFlashdata('pesan', 'Data berhasil di hapus');
        return redirect()->to(base_url('device'));
    }
}
