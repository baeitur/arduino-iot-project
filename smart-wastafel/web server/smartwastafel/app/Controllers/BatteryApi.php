<?php

namespace App\Controllers;

use App\Models\BatteryModel;

// panggil restful api codeigniter 4
use CodeIgniter\RESTful\ResourceController;

class BatteryApi extends ResourceController
{
   public function __construct()
   {
        $this->batteryModel = new BatteryModel();
   }

   public function create($data_battery=false)
   {
    if($data_battery){
        $data = [
        'battery' => $data_battery,
        ];
        //return $this->respond($data);
        $battery = $this->batteryModel->create($data);
        if ($battery) {
            $output = [
                'status'  => true,
                'message' => 'Data battery berhasil ditambahkan',
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
}
