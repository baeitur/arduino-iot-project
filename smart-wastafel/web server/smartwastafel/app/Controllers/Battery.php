<?php

namespace App\Controllers;

use App\Controllers\BaseController;

use App\Models\BatteryModel;

use function PHPSTORM_META\type;

class Battery extends BaseController
{

    public function __construct()
    {
         $this->batteryModel = new BatteryModel();
    }

    public function index()
    {
        if(!session()->has('username')){
			return redirect()->to(base_url().'/login');
		}
        $data = [
            "title" => "Smart Wastafel | Data Baterai",
            "data_battery" => $this->batteryModel->getBattery()->paginate(6,'battery'),
            "pager" => $this->batteryModel->pager
        ];
        return view('battery', $data);
    }

    public function delete($id = false)
    {
        $this->batteryModel->delete($id);
        session()->setFlashdata('pesan', 'data berhasil di hapus');
        return redirect()->to(base_url().'/battery');
    }

}
