<?php

/**
 * Application entry point.
 * @author Szymon P. Peplinski
 */
// Define application environment
defined('APPLICATION_ENV')
	|| define('APPLICATION_ENV', 
		(getenv('APPLICATION_ENV') ? getenv('APPLICATION_ENV') : 'production'));

if('production' != APPLICATION_ENV){
	defined('YII_DEBUG') or define('YII_DEBUG', true);
	defined('YII_TRACE_LEVEL') or define('YII_TRACE_LEVEL', 3);
}else{
	if(isset($_REQUEST['debug']) && (1 == $_REQUEST['debug'])){
		defined('YII_DEBUG') or define('YII_DEBUG', true);
	}
}

$yii=dirname(__FILE__).'/../yii/framework/yii.php';
$config=dirname(__FILE__).'/protected/config/'.APPLICATION_ENV.'.php';

require_once($yii);

Yii::createWebApplication($config)->run();
