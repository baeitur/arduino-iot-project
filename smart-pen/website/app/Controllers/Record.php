<?php

namespace App\Controllers;

use App\Models\RecordModel;
use App\Models\DokterModel;
use App\Models\PasienModel;

class Record extends BaseController
{

    public function __construct()
    {
        $this->statusLogin();
        $this->aksesDokter(session()->get("user_akses"));
        $this->dokterModel = new DokterModel;   
        $this->pasienModel = new PasienModel; 
        $this->recordModel = new RecordModel;
    }

    public function index()
    {            
        $data = [
            'title' => 'Medical Record',
            'datas' => $this->recordModel->getJoin(),           
        ];
        return view('record/index',$data);
    }


   
    public function add()
    {            
        $data = [
            'title' => 'Tambah Data',  
            'validation' => \Config\Services::validation(), 
            'dokters' => $this->dokterModel->findAll(),
            'pasiens' => $this->pasienModel->findAll(),           
        ];
        return view('record/add',$data);
    }

    public function tambah(){
        
        if (!$this->validate([
            'no_rm' => [
                'rules' => 'required|is_unique[rekam_medis.no_rm]',
                'errors' => [
                    'required' => '{field} harus di isi',
                    'is_unique' => '{field} sudah terdaftar'
                ]
            ],
            'tanggal' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'id_finger' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ]
            ,
            'keluhan_utama' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'hr' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],            
            'gambar' => [
                'rules' => 'max_size[gambar,1024]|is_image[gambar]|mime_in[gambar,image/jpg,image/jpeg,image/png]',
                'errors' => [
                    'max_size' => 'ukuran gambar telalu besar',
                    'mime_in' => 'file yang di upload bukan gambar',
                    'is_image' => 'file yang di upload bukan gambar'
                ]
            ]
        ])) {

            return redirect()->to(base_url('add_record'))->withInput();
        }

        $fileFoto = $this->request->getFile('gambar');

        // cek gambar apakah tetap gambar lama
        if ($fileFoto->getError() == 4) {
            $namaFoto = 'blank.jpg';
        } else {
            // genered nama file
            $namaFoto = $fileFoto->getRandomName();
            // pindah file
            $fileFoto->move('./img/', $namaFoto);
        }

        $data = [
            'no_rm'           => $this->request->getVar('no_rm'),
            'id_finger'       => $this->request->getVar('id_finger'),
            'kode_dokter'     => $this->request->getVar('kode_dokter'),
            'tanggal'         => $this->request->getVar('tanggal'),
            'tempat'          => $this->request->getVar('tempat'),
            'keluhan_utama'   => $this->request->getVar('keluhan_utama'),
            'rsp'             => $this->request->getVar('rsp'),
            'rpd'             => $this->request->getVar('rpd'),
            'rpk'             => $this->request->getVar('rpk'),
            'tensi'           => $this->request->getVar('tensi'),
            'nadi'            => $this->request->getVar('nadi'),
            'rr'              => $this->request->getVar('rr'),
            'bb'              => $this->request->getVar('bb'),
            'hr'              => $this->request->getVar('hr'),
            'temperatur'      => $this->request->getVar('temperatur'),  
            'gula_darah'      => $this->request->getVar('gula_darah'),
            'dx'              => $this->request->getVar('dx'),
            'injeksi'         => $this->request->getVar('injeksi'),            
            'gambar'          => $namaFoto,
        ];

        //dd($data);

        $this->recordModel->insert($data);

        session()->setFlashdata('pesan', 'Data berhasil di tambahkan');

        return redirect()->to(base_url('record'));
    }

    

    public function edit($rm)
    {            
        $data = [
            'title' => 'Ubah Data', 
            'validation' => \Config\Services::validation(), 
            'data'    => $this->recordModel->getByID($rm),
            'dokters' => $this->dokterModel->findAll(),
            'pasiens' => $this->pasienModel->findAll(),           
        ];
        return view('record/edit',$data);
    }

    public function ubah($rm){
        
        if (!$this->validate([
            'no_rm' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'                    
                ]
            ],
            'tanggal' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'id_finger' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ]
            ,
            'keluhan_utama' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],
            'hr' => [
                'rules' => 'required',
                'errors' => [
                    'required' => '{field} harus di isi'
                ]
            ],            
            'gambar' => [
                'rules' => 'max_size[gambar,1024]|is_image[gambar]|mime_in[gambar,image/jpg,image/jpeg,image/png]',
                'errors' => [
                    'max_size' => 'ukuran gambar telalu besar',
                    'mime_in' => 'file yang di upload bukan gambar',
                    'is_image' => 'file yang di upload bukan gambar'
                ]
            ]
        ])) {

            return redirect()->to(base_url('edit_record/'.$rm))->withInput();
        }

        $fileFoto = $this->request->getFile('gambar');

        // cek gambar apakah tetap gambar lama
        if ($fileFoto->getError() == 4) {
            $namaFoto = $this->request->getVar('old_gambar');
        } else {
            // genered nama file
            $namaFoto = $fileFoto->getRandomName();
            // pindah file
            $fileFoto->move('./img/', $namaFoto);
            // hapus sampul lama
            if ($this->request->getVar('gambar') != 'boy.jpg') {
                unlink('./img/' . $this->request->getVar('old_gambar'));
            }
        }

        $data = [
            'no_rm'           => $rm,
            'id_finger'       => $this->request->getVar('id_finger'),
            'kode_dokter'     => $this->request->getVar('kode_dokter'),
            'tanggal'         => $this->request->getVar('tanggal'),
            'tempat'          => $this->request->getVar('tempat'),
            'keluhan_utama'   => $this->request->getVar('keluhan_utama'),
            'rsp'             => $this->request->getVar('rsp'),
            'rpd'             => $this->request->getVar('rpd'),
            'rpk'             => $this->request->getVar('rpk'),
            'tensi'           => $this->request->getVar('tensi'),
            'nadi'            => $this->request->getVar('nadi'),
            'rr'              => $this->request->getVar('rr'),
            'bb'              => $this->request->getVar('bb'),
            'hr'              => $this->request->getVar('hr'),
            'temperatur'      => $this->request->getVar('temperatur'),  
            'gula_darah'      => $this->request->getVar('gula_darah'),
            'dx'              => $this->request->getVar('dx'),
            'injeksi'         => $this->request->getVar('injeksi'),            
            'gambar'            => $namaFoto,
        ];

        //dd($data);

        $this->recordModel->save($data);

        session()->setFlashdata('pesan', 'Data berhasil di ubah');

        return redirect()->to(base_url('record'));
    }

    public function delete($rm = false)
    {
        $this->recordModel->delete($rm);
        session()->setFlashdata('pesan', 'Data berhasil di hapus');
        return redirect()->to(base_url('record'));
    }
}
