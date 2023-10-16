<?php

namespace App\Models;

use CodeIgniter\Database\MySQLi\Builder;
use CodeIgniter\Database\Query;
use CodeIgniter\Model;

class PenggunaModel extends Model
{
	protected $table = 'pengguna';
	protected $useTimestamps = true;
	protected $primaryKey = 'id';
	protected $allowedFields = [
		'user',
		'suhu',
		'videos'
	];

	public function getPengguna($id=null)
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
	public function addvideo($id = null,$video = null)
    {
		$builder = $this->table($this->table)
			->where('id', $id)
			->set('videos', $video)
			->update();
		return $builder ? true : false;
	}


	public function getStatisticPengguna()
	{
		$db = \Config\Database::connect();
		//$query = $db->query("select DATE(created_at) as tanggal,count(*) as jumlah from pengguna group by DAY(created_at) limit 15");
		$query = $db->query("SELECT * FROM (SELECT DATE(created_at) AS tanggal, count(*) AS jumlah, id FROM pengguna GROUP BY DAY(created_at) ORDER BY id DESC LIMIT 15) sub ORDER BY id ASC");
		return $query->getResultArray();
	}

	public function getMaxID()
    {
      $builder = $this->table($this->table)
                      ->selectMax($this->primaryKey)
                      ->get()->getFirstRow('array');
      return $builder;
    }
	

}
