<?php

namespace App\Controllers;

use App\Models\PenggunaModel;

use App\Models\BatteryModel;

class Home extends BaseController
{
	public function __construct()
   {
		$this->batteryModel = new BatteryModel();
		$this->penggunaModel = new PenggunaModel();
   }

	public function index()
	{
		if(!session()->has('username')){
			return redirect()->to(base_url().'/login');
		}
		$data = [
            "title" => "Smart Wastafel | Dashboard",
			"username" => session()->get('username'),
			'data_battery' => $this->batteryModel->getStatisticBattery(),
			'data_pengguna' => $this->penggunaModel->getStatisticPengguna()
        ];
		return view('dashboard',$data);
	}

	public function logout(){
		session()->remove('username');
		return redirect()->to(base_url().'/login');
	}
}
