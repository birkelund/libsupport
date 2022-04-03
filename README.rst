libsupport
==========

libsupport is a C support library.


Building
--------

libsupport uses the meson build system.

.. code::

	meson setup build
	ninja -C build

However, libsupport is intended to be built and linked as a static library.

.. code::

	libsupport_proj = subproject('libsupport',
	  default_options: [
	    'default_library=shared',
	  ], required: true,
	)


License
-------

Except where otherwise stated, all software contained within this repository is
licensed under the GNU Lesser General Public License version 2.1 or later. See
``COPYING`` for more information.
