<?php

return CMap::mergeArray(
	require(dirname(__FILE__).'/main.php'),
	array(
		'components'=>array(
			'db'=>array(
				'connectionString'=>'sqlite:/Projects/CreativeCoding/FluAlert/Backend/public/protected/data/db.sqlite',
				'emulatePrepare'=>true,
				'charset'=>'utf8',
			),
		),
	)
);