<?php

/**
 * @file
 * Custom preprocesses for layout.
 */

use Drupal\Component\Utility\Html;

/**
 * Implements hook_preprocess_HOOK().
 */
function glisseo_preprocess_glisseo_reset(&$variables) {
  if (isset($variables['content']['#entity']) && $entity = $variables['content']['#entity']) {
    // Support for contextual classes.
    $new_classes = !empty($variables['attributes']['class']) ? $variables['attributes']['class'] : [];
    $entity_type = $entity->getEntityTypeId();
    $bundle = $entity->bundle();
    $view_mode = $variables['content']['#view_mode'];
    $new_classes[] = Html::cleanCssIdentifier("$entity_type--$bundle");
    $new_classes[] = Html::cleanCssIdentifier("view-mode--$view_mode");

    switch ($entity_type) {
      case 'node':
        $entity->isPromoted() ? $new_classes[] = Html::cleanCssIdentifier('promoted') : NULL;
        $entity->isSticky() ? $new_classes[] = Html::cleanCssIdentifier('sticky') : NULL;
        !$entity->isPublished() ? $new_classes[] = Html::cleanCssIdentifier('unpublished') : NULL;
        break;
    }

    // This is allows to add this classes via third party preprocesses,
    // especially from modules, which preprocess called earlier.
    if (!empty($variables['new_classes'])) {
      $variables['new_classes'] = array_merge($variables['new_classes'], $new_classes);
    }
    else {
      $variables['new_classes'] = $new_classes;
    }
  }
}
