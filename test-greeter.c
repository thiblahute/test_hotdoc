#include "test-greeter.h"

TestGreeterCountUnit test_greeter_greet_count = 0;

/**
 * SECTION:TestGreeter
 * @title: TestGreeter
 * @short_description: a *short* description
 *
 * {{ broken-link.md }}
 *
 * This is a module to greet people.
 * Linking to #TestGreeter:count-greets
 * Linking to #TestInterfaceInterface.do_something
 * Linking to g_type_init() yo
 */

G_DEFINE_TYPE(TestGreeter, test_greeter, G_TYPE_OBJECT);

enum
{
  PROP_0,
  TEST_GREETER_PROP_COUNT_GREETS,
  PROP_LAST,
};

enum
{
  TEST_GREETER_SIGNAL_GREETED,
  LAST_SIGNAL,
};

static guint test_greeter_signals[LAST_SIGNAL] = { 0 };

static void
test_greeter_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  g_return_if_fail (TEST_IS_GREETER (object));

  switch (prop_id) {
    case TEST_GREETER_PROP_COUNT_GREETS:
      TEST_GREETER (object)->count_greets = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
test_greeter_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  g_return_if_fail (TEST_IS_GREETER (object));

  switch (prop_id) {
    case TEST_GREETER_PROP_COUNT_GREETS:
      g_value_set_boolean (value, TEST_GREETER (object)->count_greets);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
static void
test_greeter_class_init (TestGreeterClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = test_greeter_set_property;
  gobject_class->get_property = test_greeter_get_property;

  /**
   * TestGreeter:count-greets:
   *
   * Set to %FALSE if you don't want the greeter to count its greets
   * Stability: stable
   */
  g_object_class_install_property (gobject_class, TEST_GREETER_PROP_COUNT_GREETS,
      g_param_spec_boolean ("count-greets", "Count Greets", "Count the greets",
        TRUE, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  /**
   * TestGreeter::greeted:
   * @greeter: the greeter that emitted the signal
   * @name: the name that was greeted
   * @object: A random GObject
   * @other_greeter: A peer greeter, greeting is better done together
   *
   * Signals that the greeter greeted somebody.
   *
   * THIS WARNING IS EXPECTED!
   * Linking to a symbol that #does-not-exist
   * Linking to #GMutex
   *
   * Stability: unstable
   * Returns: A random string
   * Since: 0.9
   */
  test_greeter_signals[TEST_GREETER_SIGNAL_GREETED] =
      g_signal_new ("greeted", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
      0, NULL, NULL,
      g_cclosure_marshal_generic, G_TYPE_STRING, 3, G_TYPE_STRING, G_TYPE_OBJECT, TEST_TYPE_GREETER);
}

static void
test_greeter_init (TestGreeter *self)
{
  self->greet_count = 0;
}

static gchar *
translate_to_english (TestGreeter *greeter, const gchar *word)
{
  if (!g_strcmp0 (word, "Hello")) {
    return g_strdup ("Hello");
  }

  return g_strdup ("");
}

static gchar *
translate_to_french (TestGreeter *greeter, const gchar *word)
{
  if (!g_strcmp0 (word, "Hello")) {
    return g_strdup ("Bonjour");
  }

  return g_strdup("");
}

/**
 * test_greeter_deprecated_function:
 * @greeter: a random greeter
 *
 * This is just a function that we will mark as deprecated
 * because it really sucked.
 *
 * Linking to [this page](test-greeter.h)
 *
 * Mentioning %TEST_GREETER_ENGLISH by the way
 * THIS SHOULD NOT RAISE A WARNING
 * Not linking here as we escape \#not-a-link
 * Linking to #guint64
 *
 * Deprecated: 0.7
 */
void
test_greeter_deprecated_function(TestGreeter *greeter)
{
  g_print ("I am deprecated, why even use me ?\n");
}

/**
 * test_greeter_skipped_function: (skip)
 * @greeter: a random greeter
 *
 * This is just a function that is not supposed to be introspected.
 */
void
test_greeter_skipped_function(TestGreeter *greeter)
{
}

/**
 * test_greeter_ignored_function: (attributes doc.skip=true)
 *
 * There is no way this function should end up in the documentation
 */
void
test_greeter_ignored_function(TestGreeter *greeter)
{
}

/**
 * test_greeter_greet:
 * @self: The #TestGreeter
 * @name: The name to greet
 * @translator: (allow-none) (scope async): A function that will need
 * to translate "hello", or %NULL .
 *
 * Will greet whoever you want, you can specify a function
 * to translate the greetings.
 *
 * {{ includeme.markdown }}
 *
 * Just {{include something .markdown}} at the middle of a line
 *
 * And here we have a C example included from a symbol name
 *
 * {{../greeter_example.c#include_an_example_symbol[1:4][8:9]}}
 *
 * Since: 0.5
 * my_tag: baz
 */
void
test_greeter_greet (TestGreeter *self,
                    const gchar *name,
                    TestGreeterTranslateFunction translator)
{
  TestGreeterClass *tg_class = TEST_GREETER_CLASS (self);

  if (tg_class->do_greet)
    return tg_class->do_greet (self, name, translator);

  if (translator) {
    gchar *translated = translator (self, "Hello");
    g_print ("%s %s\n", translated, name);
    g_free (translated);
  } else {
    g_print ("Hello %s !\n", name);
  }

  if (self->count_greets)
    TEST_GREETER_UPDATE_GREET_COUNT(self);
}

/**
 * test_greeter_do_foo_bar:
 * @foo: (out): something to foo
 * @bar: something to bar
 *
 * This function is here to test that out parameters
 * are correctly interpreted as return values for python and javascript.
 *
 * This function also checks that referring to signals that way:
 * #TestGreeter::greeted works correctly
 *
 * Returns: A nice gchar - should be a int in python.
 * Since: 0.8
 * Topic: A topic
 * my_tag: bar
 */
gchar
test_greeter_do_foo_bar (gint *foo, gchar *bar)
{
  *foo = 57;

  return 'a';
}

/**
 * test_greeter_get_translate_function:
 * @greeter: The #TestGreeter
 * @language: The target #TestGreeterLanguage
 *
 * This function is also here to check that piped tables work.
 *
 * |  First column that is pretty long really don't you think? |  Second one |
 * |-----------------------------------------------------------|-------------|
 * | First content that can take quite some room               | And second  |
 * | a | b |
 *
 *
 * Returns: (transfer none): a #TestGreeterTranslateFunction for the target @language or %NULL.
 * Stability: unstable
 */
TestGreeterTranslateFunction
test_greeter_get_translate_function (TestGreeter *greeter, TestGreeterLanguage language)
{
  switch (language) {
    case TEST_GREETER_ENGLISH:
      return translate_to_english;
    case TEST_GREETER_FRENCH:
      return translate_to_french;
    default:
      break;
  }

  return NULL;
}

/**
 * test_greeter_list_greets:
 * @greeter: The greatest greeter
 *
 * Testing returnins a list of strings.
 *
 * Returns: (transfer full): The list of greetings @greeter can do
 */
gchar **
test_greeter_list_greets (TestGreeter *greeter)
{
    return NULL;
}

/**
 * test_greeter_list_languages:
 * @greeter: The greatest greeter
 *
 * Testing list of structs as return value.
 *
 * Returns: (array zero-terminated=1): The list of languages @greeter can speak
 */
TestGreeterLanguage *
test_greeter_list_languages (TestGreeter *greeter)
{
    static TestGreeterLanguage languages[] = {TEST_GREETER_FRENCH, 0};

    return languages;
}

/**
 * test_greeter_get_friends:
 * @greeter: The greatest greeter
 *
 * Test rendering a GList of object as return value,
 * in python it should properly show the return value
 * is a list.
 *
 * Returns: (transfer full) (element-type TestGreeter): The **list** of the friends of @greeter
 */
GList*
test_greeter_get_friends (TestGreeter *greeter, GError **error)
{
  return NULL;
}

/**
 * test_greeter_get_out_glist_friends:
 * @greeter: The greatest greeter
 * @friends: (out) (transfer full) (element-type TestGreeter): The **glist** of the friends of @greeter
 *
 * Test rendering a GList of object as out return value,
 * in python it should properly show the out return value
 * is a list.
 *
 * Returns: %TRUE if @friends could be retrived.
 */
gboolean
test_greeter_get_out_glist_friends (TestGreeter *greeter, GList ** friends)
{
  *friends = NULL;
  return FALSE;
}

/**
 * test_greeter_get_out_friends:
 * @greeter: The greatest greeter
 * @friends: (out)(array zero-terminated=1)(transfer full): The **list** of the friends of @greeter
 *
 * Test rendering an of object as out return value,
 * in python it should properly show the out return value
 * is a list.
 *
 * Returns: %TRUE if @friends could be retrived.
 */
gboolean
test_greeter_get_out_friends (TestGreeter *greeter, TestGreeter *** friends)
{
  *friends = NULL;
  return FALSE;
}

/**
 * test_greeter_has_friends:
 * @greeter: The greatest greeter
 * @friends: (element-type TestGreeter): The friends to check
 *
 * Test rendering a GList of object as input, in python it should properly show @friends
 * is a list.
 *
 * Returns: %TRUE all the time, @greet is friendly.
 */
gboolean
test_greeter_has_friends (TestGreeter *greeter, GList *friends)
{
    return TRUE;
}

/**
 * test_greeter_languages_contains:
 * @languages: (array zero-terminated=1): The language array to search
 * @language: the language to find
 *
 * Testing list of structs as parametter.
 *
 * Returns: %TRUE if the language is found inside the array
 */
gboolean
test_greeter_languages_contains (TestGreeterLanguage * languages,
        TestGreeterLanguage language)
{
  return FALSE;
}
