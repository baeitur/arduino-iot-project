<?php

namespace App\Controllers;

use App\Models\DokterModel;
use App\Models\DeviceModel;

class Dokter extends BaseController
{

    public function __construct()
    {
        $this->statusLogin();
        $this->aksesAdmin(session()->get("user_akses"));
        $this->dokterModel = new DokterModel;   
        $this->deviceModel = new DeviceModel;     
    }

    public function index()
    {            
        $data = [
            'title' => 'Data Dokter',
            'datas' => $this->dokterModel->findAll(),                 
        ];        
        return view('dokter/index',$data);
    }

    public function add()
    {      
        $device = $this->deviceModel->where('status', '0')->findAll();
        if(empty($device)){
            session()->setFlashdata('pesan', 'Data device kosong.!');
            return redirect()->to(base_url('dokter'));
        }      
        $data = [
            'title' => 'Tambah Data',  
            'validation' => \Config\Services::validation(), 
            'devices' => $device,             
        ];
        return view('dokter/add',$data);
    }

    public function tambah(){
        
        if (!$this->validate([
            'kode_dokter' => [
                'rules' => 'required|is_unique[dokter.serial_device]',
                'errors' => [
                    'required' => '{field} harus di isi',
                    'is_unique' => '{field} sudah terdaftar'
                ]
            ],
            'nama_dokter' => [
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
            ]
            ,
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
            ],
            'spesialisasi' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],

            'serial_device' => [
                'rules' => 'required|is_unique[dokter.serial_device]',
                'errors' => [
                    'required' => '{field} harus di isi',
                    'is_unique' => '{field} sudah terdaftar'
                ]
            ],
            'foto' => [
                'rules' => 'max_size[foto,1024]|is_image[foto]|mime_in[foto,image/jpg,image/jpeg,image/png]',
                'errors' => [
                    'max_size' => 'ukuran gambar telalu besar',
                    'mime_in' => 'file yang di upload bukan gambar',
                    'is_image' => 'file yang di upload bukan gambar'
                ]
            ]
        ])) {

            return redirect()->to(base_url('add_dokter'))->withInput();
        }

        $fileFoto = $this->request->getFile('foto');

        // cek gambar apakah tetap gambar lama
        if ($fileFoto->getError() == 4) {
            $namaFoto = 'boy.png';
        } else {
            // genered nama file
            $namaFoto = $fileFoto->getRandomName();
            // pindah file
            $fileFoto->move('./img/', $namaFoto);
        }

        $data = [
            'kode_dokter'     => $this->request->getVar('kode_dokter'),
            'nama_dokter'     => $this->request->getVar('nama_dokter'),
            'alamat'          => $this->request->getVar('alamat'),
            'jenis_kelamin'   => $this->request->getVar('jenis_kelamin'),
            'tempat_lahir'    => $this->request->getVar('tempat_lahir'),
            'tanggal_lahir'   => $this->request->getVar('tanggal_lahir'),
            'spesialisasi'    => $this->request->getVar('spesialisasi'),
            'no_telepon'      => $this->request->getVar('no_telepon'),
            'serial_device'   => $this->request->getVar('serial_device'),
            'password'        => password_hash('12345678', PASSWORD_BCRYPT),
            'foto'            => $namaFoto,
        ];

        //dd($data);

        $this->dokterModel->insert($data);

        $data = [
            'serial_device'   => $this->request->getVar('serial_device'),
            'status'          => 1
        ];

        $this->deviceModel->save($data);

        session()->setFlashdata('pesan', 'Data berhasil di tambahkan');

        return redirect()->to(base_url('dokter'));
    }

    public function edit($kode)
    {            
        $data = [
            'title' => 'Ubah Data',  
            'validation' => \Config\Services::validation(), 
            'data' => $this->dokterModel->getByID($kode),
            'devices' => $this->deviceModel->findAll(),            
        ];
        return view('dokter/edit',$data);
    }

    public function ubah($kode){
        
        if (!$this->validate([
            'kode_dokter' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'                    
                ]
            ],
            'nama_dokter' => [
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
            ]
            ,
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
            ],
            'spesialisasi' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],

            'serial_device' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'                    
                ]
            ],
            'foto' => [
                'rules' => 'max_size[foto,1024]|is_image[foto]|mime_in[foto,image/jpg,image/jpeg,image/png]',
                'errors' => [
                    'max_size' => 'ukuran gambar telalu besar',
                    'mime_in' => 'file yang di upload bukan gambar',
                    'is_image' => 'file yang di upload bukan gambar'
                ]
            ]
        ])) {

            return redirect()->to(base_url('add_dokter'))->withInput();
        }

        $fileFoto = $this->request->getFile('foto');

        // cek gambar apakah tetap gambar lama
        if ($fileFoto->getError() == 4) {
            $namaFoto = $this->request->getVar('old_foto');
        } else {
            // genered nama file
            $namaFoto = $fileFoto->getRandomName();
            // pindah file
            $fileFoto->move('./img/', $namaFoto);
            // hapus sampul lama
            if ($this->request->getVar('foto') != 'boy.jpg') {
                unlink('./img/' . $this->request->getVar('old_foto'));
            }
        }

        $data = [
            'kode_dokter'     => $this->request->getVar('kode_dokter'),
            'nama_dokter'     => $this->request->getVar('nama_dokter'),
            'alamat'          => $this->request->getVar('alamat'),
            'jenis_kelamin'   => $this->request->getVar('jenis_kelamin'),
            'tempat_lahir'    => $this->request->getVar('tempat_lahir'),
            'tanggal_lahir'   => $this->request->getVar('tanggal_lahir'),
            'spesialisasi'    => $this->request->getVar('spesialisasi'),
            'no_telepon'      => $this->request->getVar('no_telepon'),
            'serial_device'   => $this->request->getVar('serial_device'),
            'foto'            => $namaFoto,
        ];

        //dd($data);

        $this->dokterModel->save($data);

        session()->setFlashdata('pesan', 'Data berhasil di ubah');

        return redirect()->to(base_url('dokter'));
    }

    public function delete($kode = false)
    {
        $this->dokterModel->delete($kode);
        session()->setFlashdata('pesan', 'Data berhasil di hapus');
        return redirect()->to(base_url('dokter'));
    }
}
