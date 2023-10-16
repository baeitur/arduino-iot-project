<?php

namespace App\Models;

use CodeIgniter\Model;

class DeviceModel extends Model
{
    protected $table    = 'device';
    protected $primaryKey = 'serial_device';
    protected $useTimestamps = true;

    protected $allowedFields = ['serial_device','start_id','end_id','status'];

    public function getFirst()
    {
        $builder = $this->table($this->table)
            ->get()->getFirstRow('array');
        return $builder;
    }

    public function getByID($serial)
    {
        $builder = $this->table($this->table)
            ->where($this->primaryKey,$serial)
            ->get()->getFirstRow('array');
        return $builder;
    }
}
