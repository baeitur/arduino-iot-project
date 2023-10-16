<?php

namespace App\Controllers;

use App\Controllers\BaseController;

use App\Models\PenggunaModel;

use function PHPSTORM_META\type;

class Pengguna extends BaseController
{

    public function __construct()
    {
         $this->penggunaModel = new PenggunaModel();
    }

    public function index()
    {
        if(!session()->has('username')){
			return redirect()->to('/login');
		}
        $data = [
            "title" => "Smart Wastafel | Data Pengguna",
            "data_pengguna" => $this->penggunaModel->getPengguna()->paginate(6,'pengguna'),
            "pager" => $this->penggunaModel->pager
        ];
        return view('pengguna', $data);
    }

    public function delete($id = false, $video=null)
    {
        $this->penggunaModel->delete($id);
        unlink('./videos/' . $video);
        session()->setFlashdata('pesan', 'data berhasil di hapus');
        return redirect()->to(base_url().'/pengguna');
    }


    //--------------------------------------------------------------------

}
