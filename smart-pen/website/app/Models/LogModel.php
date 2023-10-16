<?php

namespace App\Models;

use CodeIgniter\Model;

class LogModel extends Model
{
    protected $table    = 'log';
    protected $primaryKey = 'id';
    protected $useTimestamps = true;

    protected $allowedFields = ['id_finger','message'];

    public function getFirst()
    {
        $builder = $this->table($this->table)
            ->get()->getFirstRow('array');
        return $builder;
    }

    public function getJoin($id_finger)
    {   
        $db = \Config\Database::connect();
        $builder = $db->table('rekam_medis')
            ->where('rekam_medis.id_finger',$id_finger)
            ->join('pasien', 'pasien.id_finger = rekam_medis.id_finger')
            ->join('dokter', 'dokter.kode_dokter = rekam_medis.kode_dokter','FULL')
            ->get()->getResultArray();            
        return $builder;
    }

    public function getRm($no_rm)
    {   
        $db = \Config\Database::connect();
        $builder = $db->table('rekam_medis')
            ->where('rekam_medis.no_rm',$no_rm)
            ->join('pasien', 'pasien.id_finger = rekam_medis.id_finger')
            ->join('dokter', 'dokter.kode_dokter = rekam_medis.kode_dokter','FULL')
            ->get()->getFirstRow('array');            
        return $builder;
    }
}
