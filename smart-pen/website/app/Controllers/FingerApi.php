<?php

namespace App\Controllers;

use CodeIgniter\RESTful\ResourceController;

use App\Models\LogModel;
use App\Models\PasienModel;

class FingerApi extends ResourceController
{
   public function __construct(){
       $this->logModel = new LogModel;
       $this->pasienModel = new PasienModel;
   }

   public function finger($id_finger)
   {   

    $pasien = $this->pasienModel->getByID($id_finger);
    $find_data = $this->logModel->getJoin($id_finger);

    if(!$pasien){
        $data = [
            'id'=> 1,
            'id_finger'=> $id_finger,
            'message'=> 0
        ];
        $this->logModel->save($data);
        return $this->respond([
            'status'=> 'ID finger Not Found!'
        ]);  
    }else if((!$find_data)){
        $data = [
            'id'=> 1,
            'id_finger'=> $id_finger,
            'message'=> 1
        ];
        $this->logModel->save($data);
        return $this->respond([
            'nama'  => $pasien['nama_pasien'],
            'status'=> 'Data not found!',
        ]);       
    }else{
        $data = [
            'id'=> 1,
            'id_finger'=> $id_finger,
            'message'=> 2
        ];
        $this->logModel->save($data);
        return $this->respond([
                                'nama'  => $pasien['nama_pasien'],
                                'status'=> 'Sukses',
                            ]);    
    }                       
            
   }
}