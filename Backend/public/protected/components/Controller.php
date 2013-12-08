<?php

/**
 * Controller is the customized base controller class.
 * All controller classes for this application should extend from this base class.
 * @author Szymon P. Peplinski <szymon.peplinski@tribalddb.pl>
 */
class Controller extends CController
{
	/**
	 * @var string the default layout for the controller view. Defaults to '//layouts/content',
	 * meaning using a single column layout. See 'protected/views/layouts/content.php'.
	 */
	public $layout='//layouts/content';
	/**
	 * @var array context menu items. This property will be assigned to {@link CMenu::items}.
	 */
	public $menu=array();
	/**
	 * @var array the breadcrumbs of the current page. The value of this property will
	 * be assigned to {@link CBreadcrumbs::links}. Please refer to {@link CBreadcrumbs::links}
	 * for more details on how to specify this property.
	 */
	public $breadcrumbs=array();
	
	function __construct($id,$module=null)
	{
		parent::__construct($id,$module);
	}
}