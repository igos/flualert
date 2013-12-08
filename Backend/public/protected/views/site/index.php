<?php

$clientScript=Yii::app()->clientScript;
$clientScript->registerScriptFile(Yii::app()->baseUrl.'/js/swfobject.js',CClientScript::POS_HEAD);
$clientScript->registerScript('script','
	// Internet Explorer Fallback.
	var alertFallback=true;
	if(typeof console==="undefined"||typeof console.log==="undefined"){console={};if(alertFallback){console.log=function(msg){};}else{console.log=function(){};}};
',CClientScript::POS_END);

?>Hello #hackwaw ! <?php echo $id; ?>