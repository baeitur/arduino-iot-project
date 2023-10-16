<?php

namespace App\Models;

use CodeIgniter\Model;

class RecordModel extends Model
{
    protected $table    = 'rekam_medis';
    protected $primaryKey = 'no_rm';
    protected $useTimestamps = true;

    protected $allowedFields = ['no_rm','id_finger','kode_dokter','tanggal','tempat','keluhan_utama','rsp','rpd','rpk','tensi','nadi','rr','bb','hr','temperatur','gula_darah','dx','injeksi','gambar'];

    public function getFirst()
    {
        $builder = $this->table($this->table)
            ->get()->getFirstRow('array');
        return $builder;
    }

    public function getByID($rm)
    {
        $builder = $this->table($this->table)
            ->where($this->primaryKey,$rm)
            ->get()->getFirstRow('array');
        return $builder;
    }

    public function getJoin()
    {
        $builder = $this->table($this->table)
            ->join('pasien', 'pasien.id_finger = rekam_medis.id_finger')
            ->join('dokter', 'dokter.kode_dokter = rekam_medis.kode_dokter','FULL')
            ->get()->getResultArray();
        return $builder;
    }
}
