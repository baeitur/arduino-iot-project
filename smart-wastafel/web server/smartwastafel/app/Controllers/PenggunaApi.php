<?php

namespace App\Controllers;

use App\Models\PenggunaModel;

// panggil restful api codeigniter 4
use CodeIgniter\RESTful\ResourceController;

class PenggunaApi extends ResourceController
{
   public function __construct()
   {
        $this->penggunaModel = new PenggunaModel();
   }

   public function create($data_pengguna = false, $data_suhu = false)
   {
    if($data_pengguna && $data_suhu){
        $data = [
        'user' => $data_pengguna,
        'suhu' => $data_suhu,
        'videos' => ''
        ];
        //return $this->respond($data);
        $pengguna = $this->penggunaModel->create($data);
        if ($pengguna) {
            $output = [
                'status'  => true,
                'message' => 'Data pengguna berhasil ditambahkan',
            ];
            return $this->respond($output);
        } 
    }else {
       $output = [
          'status' => false,
          'message' => 'Data gagal ditambahkan'
       ];
       return $this->respond($output);
    }
   }

   public function update($videos = false)
   {
    if($videos){      
        $id = $this->penggunaModel->getMaxID();
        //return $this->respond($data);
        $status = $this->penggunaModel->addVideo($id['id'], $videos);
        if ($status) {
            $output = [
                'status'  => true,
                'message' => 'Data video berhasil di tambahkan',
            ];
            return $this->respond($output);
        } 
    }else {
       $output = [
          'status' => false,
          'message' => 'Data video gagal di tambahakan'
       ];
       return $this->respond($output);
    }
   }
}
