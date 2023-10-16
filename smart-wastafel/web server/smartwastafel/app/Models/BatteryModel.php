<?php

namespace App\Models;

use CodeIgniter\Database\MySQLi\Builder;
use CodeIgniter\Database\Query;
use CodeIgniter\Model;

class BatteryModel extends Model
{
	protected $table = 'battery';
	protected $useTimestamps = true;
	protected $primaryKey = 'id';
	protected $allowedFields = [
		'battery'
	];

	public function getBattery($id=null)
	{
		$builder = $this->table($this->table)
			->orderBy($this->primaryKey, 'DESC');
		return $builder;
	}

	public function create($data = null)
    {
      $builder = $this->table($this->table)
         ->insert($data);
      return $builder ? true : false;
	}
	
	public function getStatisticBattery()
    {
		$db = \Config\Database::connect();
		//$query = $db->query("select TIME(created_at) as time, battery, id from battery");
		$query = $db->query("SELECT * FROM (SELECT TIME(created_at) as time, battery, id FROM battery ORDER BY id DESC LIMIT 15) sub ORDER BY id ASC");
		//dd($query->getResultArray());
		return $query->getResultArray();
    }


}
