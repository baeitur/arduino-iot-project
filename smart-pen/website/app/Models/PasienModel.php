<?php

namespace App\Models;

use CodeIgniter\Model;

class PasienModel extends Model
{
    protected $table    = 'pasien';
    protected $primaryKey = 'id_finger';
    protected $useTimestamps = true;

    protected $allowedFields = ['id_finger','nama_pasien','no_identitas','alamat','jenis_kelamin','golongan_darah','tempat_lahir','tanggal_lahir','agama','no_telepon'];

    public function getFirst()
    {
        $builder = $this->table($this->table)
            ->get()->getFirstRow('array');
        return $builder;
    }

    public function getByID($id_finger)
    {
        $builder = $this->table($this->table)
            ->where($this->primaryKey,$id_finger)
            ->get()->getFirstRow('array');
        return $builder;
    }
}
