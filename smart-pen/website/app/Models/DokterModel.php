<?php

namespace App\Models;

use CodeIgniter\Model;

class DokterModel extends Model
{
    protected $table    = 'dokter';
    protected $primaryKey = 'kode_dokter';
    protected $useTimestamps = true;

    protected $allowedFields = ['kode_dokter','nama_dokter','alamat','jenis_kelamin','tempat_lahir','tanggal_lahir','spesialisasi','no_telepon','serial_device','password','foto'];

    public function getFirst()
    {
        $builder = $this->table($this->table)
            ->get()->getFirstRow('array');
        return $builder;
    }

    public function getByID($kode)
    {
        $builder = $this->table($this->table)
            ->where($this->primaryKey,$kode)
            ->get()->getFirstRow('array');
        return $builder;
    }

    public function cek_login($kode)
    {
        $query = $this->table($this->table)
            ->where('kode_dokter', $kode)
            ->countAll();

        if ($query > 0) {
            $hasil = $this->table($this->table)
                ->where('kode_dokter', $kode)
                ->get()->getFirstRow('array');
        } else {
            $hasil = array();
        }
        return $hasil;
    }
}
