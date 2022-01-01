/* -*- c++ -*- */
/*
 * Copyright 2012 Dimitri Stolnikov <horiz0n@gmx.net>
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * config.h is generated by configure.  It contains the results
 * of probing for features, options etc.  It should be the first
 * file included in your .cc file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <gnuradio/blocks/null_source.h>
#include <gnuradio/blocks/throttle.h>
#include <gnuradio/constants.h>

#ifdef ENABLE_OSMOSDR
#include <osmosdr_src_c.h>
#endif

#ifdef ENABLE_FCD
#include <fcd_source_c.h>
#endif

#ifdef ENABLE_FILE
#include <file_source_c.h>
#endif

#ifdef ENABLE_RTL
#include <rtl_source_c.h>
#endif

#ifdef ENABLE_RTL_TCP
#include <rtl_tcp_source_c.h>
#endif

#ifdef ENABLE_UHD
#include <uhd_source_c.h>
#endif

#ifdef ENABLE_MIRI
#include <miri_source_c.h>
#endif

#ifdef ENABLE_SDRPLAY
#include <sdrplay_source_c.h>
#endif

#ifdef ENABLE_HACKRF
#include <hackrf_source_c.h>
#endif

#ifdef ENABLE_BLADERF
#include <bladerf_source_c.h>
#endif

#ifdef ENABLE_RFSPACE
#include <rfspace_source_c.h>
#endif

#ifdef ENABLE_AIRSPY
#include <airspy_source_c.h>
#endif

#ifdef ENABLE_AIRSPYHF
#include <airspyhf_source_c.h>
#endif

#ifdef ENABLE_SOAPY
#include <soapy_source_c.h>
#endif

#ifdef ENABLE_REDPITAYA
#include <redpitaya_source_c.h>
#endif

#ifdef ENABLE_FREESRP
#include <freesrp_source_c.h>
#endif

#include "arg_helpers.h"
#include "source_impl.h"

/*
 * Create a new instance of source_impl and return
 * a boost shared_ptr.  This is effectively the public constructor.
 */
osmosdr::source::sptr
osmosdr::source::make( const std::string &args )
{
  return gnuradio::get_initial_sptr( new source_impl(args) );
}

/*
 * The private constructor
 */
source_impl::source_impl( const std::string &args )
  : gr::hier_block2 ("source_impl",
        gr::io_signature::make(0, 0, 0),
        args_to_io_signature(args)),
    _sample_rate(NAN)
{
  size_t channel = 0;
  bool device_specified = false;

  std::vector< std::string > arg_list = args_to_vector(args);

  std::vector< std::string > dev_types;

#ifdef ENABLE_FILE
  dev_types.push_back("file");
#endif
#ifdef ENABLE_OSMOSDR
  dev_types.push_back("osmosdr");
#endif
#ifdef ENABLE_FCD
  dev_types.push_back("fcd");
#endif
#ifdef ENABLE_RTL
  dev_types.push_back("rtl");
#endif
#ifdef ENABLE_RTL_TCP
  dev_types.push_back("rtl_tcp");
#endif
#ifdef ENABLE_UHD
  dev_types.push_back("uhd");
#endif
#ifdef ENABLE_MIRI
  dev_types.push_back("miri");
#endif
#ifdef ENABLE_SDRPLAY
  dev_types.push_back("sdrplay");
#endif
#ifdef ENABLE_HACKRF
  dev_types.push_back("hackrf");
#endif
#ifdef ENABLE_BLADERF
  dev_types.push_back("bladerf");
#endif
#ifdef ENABLE_RFSPACE
  dev_types.push_back("rfspace");
#endif
#ifdef ENABLE_AIRSPY
  dev_types.push_back("airspy");
#endif
#ifdef ENABLE_AIRSPYHF
  dev_types.push_back("airspyhf");
#endif
#ifdef ENABLE_SOAPY
  dev_types.push_back("soapy");
#endif
#ifdef ENABLE_REDPITAYA
  dev_types.push_back("redpitaya");
#endif
#ifdef ENABLE_FREESRP
  dev_types.push_back("freesrp");
#endif
  std::cerr << "gr-osmosdr "
            << GR_OSMOSDR_VERSION << " (" << GR_OSMOSDR_LIBVER << ") "
            << "gnuradio " << gr::version() << std::endl;
  std::cerr << "built-in source types: ";
  BOOST_FOREACH(std::string dev_type, dev_types)
    std::cerr << dev_type << " ";
  std::cerr << std::endl;

#ifdef ENABLE_RFSPACE
  dev_types.push_back("sdr-iq"); /* additional aliases for rfspace backend */
  dev_types.push_back("sdr-ip");
  dev_types.push_back("netsdr");
  dev_types.push_back("cloudiq");
#endif

  BOOST_FOREACH(std::string arg, arg_list) {
    dict_t dict = params_to_dict(arg);
    BOOST_FOREACH(std::string dev_type, dev_types) {
      if ( dict.count( dev_type ) ) {
        device_specified = true;
        break;
      }
    }
  }

  if ( ! device_specified ) {
    std::vector< std::string > dev_list;
#ifdef ENABLE_OSMOSDR
    BOOST_FOREACH( std::string dev, osmosdr_src_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_FCD
    BOOST_FOREACH( std::string dev, fcd_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_RTL
    BOOST_FOREACH( std::string dev, rtl_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_UHD
    BOOST_FOREACH( std::string dev, uhd_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_MIRI
    BOOST_FOREACH( std::string dev, miri_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_SDRPLAY
    BOOST_FOREACH( std::string dev, sdrplay_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_BLADERF
    BOOST_FOREACH( std::string dev, bladerf_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_RFSPACE
    BOOST_FOREACH( std::string dev, rfspace_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_HACKRF
    BOOST_FOREACH( std::string dev, hackrf_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_AIRSPY
    BOOST_FOREACH( std::string dev, airspy_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_AIRSPYHF
    BOOST_FOREACH( std::string dev, airspyhf_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_SOAPY
    BOOST_FOREACH( std::string dev, soapy_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_REDPITAYA
    BOOST_FOREACH( std::string dev, redpitaya_source_c::get_devices() )
      dev_list.push_back( dev );
#endif
#ifdef ENABLE_FREESRP
    BOOST_FOREACH( std::string dev, freesrp_source_c::get_devices() )
      dev_list.push_back( dev );
#endif

//    std::cerr << std::endl;
//    BOOST_FOREACH( std::string dev, dev_list )
//      std::cerr << "'" << dev << "'" << std::endl;

    if ( dev_list.size() )
      arg_list.push_back( dev_list.front() );
    else
      throw std::runtime_error("No supported devices found (check the connection and/or udev rules).");
  }

  BOOST_FOREACH(std::string arg, arg_list) {

    dict_t dict = params_to_dict(arg);

//    std::cerr << std::endl;
//    BOOST_FOREACH( dict_t::value_type &entry, dict )
//      std::cerr << "'" << entry.first << "' = '" << entry.second << "'" << std::endl;

    source_iface *iface = NULL;
    gr::basic_block_sptr block;

#ifdef ENABLE_OSMOSDR
    if ( dict.count("osmosdr") ) {
      osmosdr_src_c_sptr src = osmosdr_make_src_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_FCD
    if ( dict.count("fcd") ) {
      fcd_source_c_sptr src = make_fcd_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_FILE
    if ( dict.count("file") ) {
      file_source_c_sptr src = make_file_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_RTL
    if ( dict.count("rtl") ) {
      rtl_source_c_sptr src = make_rtl_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_RTL_TCP
    if ( dict.count("rtl_tcp") ) {
      rtl_tcp_source_c_sptr src = make_rtl_tcp_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_UHD
    if ( dict.count("uhd") ) {
      uhd_source_c_sptr src = make_uhd_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_MIRI
    if ( dict.count("miri") ) {
      miri_source_c_sptr src = make_miri_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_SDRPLAY
    if ( dict.count("sdrplay") ) {
      sdrplay_source_c_sptr src = make_sdrplay_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_HACKRF
    if ( dict.count("hackrf") ) {
      hackrf_source_c_sptr src = make_hackrf_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_BLADERF
    if ( dict.count("bladerf") ) {
      bladerf_source_c_sptr src = make_bladerf_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_RFSPACE
    if ( dict.count("rfspace") ||
         dict.count("sdr-iq") ||
         dict.count("sdr-ip") ||
         dict.count("netsdr") ||
         dict.count("cloudiq") ) {
      rfspace_source_c_sptr src = make_rfspace_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_AIRSPY
    if ( dict.count("airspy") ) {
      airspy_source_c_sptr src = make_airspy_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_AIRSPYHF
    if ( dict.count("airspyhf") ) {
      airspyhf_source_c_sptr src = make_airspyhf_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_SOAPY
    if ( dict.count("soapy") ) {
      soapy_source_c_sptr src = make_soapy_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_REDPITAYA
    if ( dict.count("redpitaya") ) {
      redpitaya_source_c_sptr src = make_redpitaya_source_c( arg );
      block = src; iface = src.get();
    }
#endif

#ifdef ENABLE_FREESRP
    if ( dict.count("freesrp") ) {
      freesrp_source_c_sptr src = make_freesrp_source_c( arg );
      block = src; iface = src.get();
    }
#endif

    if ( iface != NULL && long(block.get()) != 0 ) {
      _devs.push_back( iface );

      for (size_t i = 0; i < iface->get_num_channels(); i++) {
#ifdef HAVE_IQBALANCE
        gr::iqbalance::optimize_c::sptr iq_opt = gr::iqbalance::optimize_c::make( 0 );
        gr::iqbalance::fix_cc::sptr     iq_fix = gr::iqbalance::fix_cc::make();

        connect(block, i, iq_fix, 0);
        connect(iq_fix, 0, self(), channel++);

        connect(block, i, iq_opt, 0);
        msg_connect(iq_opt, "iqbal_corr", iq_fix, "iqbal_corr");

        _iq_opt.push_back( iq_opt.get() );
        _iq_fix.push_back( iq_fix.get() );
#else
        connect(block, i, self(), channel++);
#endif
      }
    } else if ( (iface != NULL) || (long(block.get()) != 0) )
      throw std::runtime_error("Either iface or block are NULL.");

  }

  if (!_devs.size())
    throw std::runtime_error("No devices specified via device arguments.");
}

size_t source_impl::get_num_channels()
{
  size_t channels = 0;

  BOOST_FOREACH( source_iface *dev, _devs )
    channels += dev->get_num_channels();

  return channels;
}

bool source_impl::seek( long seek_point, int whence, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->seek( seek_point, whence, dev_chan );

  return false;
}

#define NO_DEVICES_MSG  "FATAL: No device(s) available to work with."

osmosdr::meta_range_t source_impl::get_sample_rates()
{
  if ( ! _devs.empty() )
    return _devs[0]->get_sample_rates(); // assume same devices used in the group
#if 0
  else
    throw std::runtime_error(NO_DEVICES_MSG);
#endif
  return osmosdr::meta_range_t();;
}

double source_impl::set_sample_rate(double rate)
{
  double sample_rate = 0;

  if (_sample_rate != rate) {
#if 0
    if (_devs.empty())
      throw std::runtime_error(NO_DEVICES_MSG);
#endif
    BOOST_FOREACH( source_iface *dev, _devs )
      sample_rate = dev->set_sample_rate(rate);

#ifdef HAVE_IQBALANCE
    size_t channel = 0;
    BOOST_FOREACH( source_iface *dev, _devs ) {
      for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++) {
        if ( channel < _iq_opt.size() ) {
          gr::iqbalance::optimize_c *opt = _iq_opt[channel];

          if ( opt->period() > 0 ) { /* optimize is enabled */
            opt->set_period( dev->get_sample_rate() / 5 );
            opt->reset();
          }
        }

        channel++;
      }
    }
#endif

    _sample_rate = sample_rate;
  }

  return _sample_rate;
}

double source_impl::get_sample_rate()
{
  double sample_rate = 0;

  if (!_devs.empty())
    sample_rate = _devs[0]->get_sample_rate(); // assume same devices used in the group
#if 0
  else
    throw std::runtime_error(NO_DEVICES_MSG);
#endif
  return sample_rate;
}

osmosdr::freq_range_t source_impl::get_freq_range( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_freq_range( dev_chan );

  return osmosdr::freq_range_t();
}

double source_impl::set_center_freq( double freq, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ ) {
        if ( _center_freq[ chan ] != freq ) {
          _center_freq[ chan ] = freq;
          return dev->set_center_freq( freq, dev_chan );
        } else { return _center_freq[ chan ]; }
      }

  return 0;
}

double source_impl::get_center_freq( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_center_freq( dev_chan );

  return 0;
}

double source_impl::set_freq_corr( double ppm, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ ) {
        if ( _freq_corr[ chan ] != ppm ) {
          _freq_corr[ chan ] = ppm;
          return dev->set_freq_corr( ppm, dev_chan );
        } else { return _freq_corr[ chan ]; }
      }

  return 0;
}

double source_impl::get_freq_corr( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_freq_corr( dev_chan );

  return 0;
}

std::vector<std::string> source_impl::get_gain_names( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_gain_names( dev_chan );

  return std::vector< std::string >();
}

osmosdr::gain_range_t source_impl::get_gain_range( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_gain_range( dev_chan );

  return osmosdr::gain_range_t();
}

osmosdr::gain_range_t source_impl::get_gain_range( const std::string & name, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_gain_range( name, dev_chan );

  return osmosdr::gain_range_t();
}

bool source_impl::set_gain_mode( bool automatic, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ ) {
        if ( (_gain_mode.count(chan) == 0) || (_gain_mode[ chan ] != automatic) ) {
          _gain_mode[ chan ] = automatic;
          bool mode = dev->set_gain_mode( automatic, dev_chan );
          if (!automatic) // reapply gain value when switched to manual mode
            dev->set_gain( _gain[ chan ], dev_chan );
          return mode;
        } else { return _gain_mode[ chan ]; }
      }

  return false;
}

bool source_impl::get_gain_mode( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_gain_mode( dev_chan );

  return false;
}

double source_impl::set_gain( double gain, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ ) {
        if ( _gain[ chan ] != gain ) {
          _gain[ chan ] = gain;
          return dev->set_gain( gain, dev_chan );
        } else { return _gain[ chan ]; }
      }

  return 0;
}

double source_impl::set_gain( double gain, const std::string & name, size_t chan)
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->set_gain( gain, name, dev_chan );

  return 0;
}

double source_impl::get_gain( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_gain( dev_chan );

  return 0;
}

double source_impl::get_gain( const std::string & name, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_gain( name, dev_chan );

  return 0;
}

double source_impl::set_if_gain( double gain, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ ) {
        if ( _if_gain[ chan ] != gain ) {
          _if_gain[ chan ] = gain;
          return dev->set_if_gain( gain, dev_chan );
        } else { return _if_gain[ chan ]; }
      }

  return 0;
}

double source_impl::set_bb_gain( double gain, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ ) {
        if ( _bb_gain[ chan ] != gain ) {
          _bb_gain[ chan ] = gain;
          return dev->set_bb_gain( gain, dev_chan );
        } else { return _bb_gain[ chan ]; }
      }

  return 0;
}

std::vector< std::string > source_impl::get_antennas( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_antennas( dev_chan );

  return std::vector< std::string >();
}

std::string source_impl::set_antenna( const std::string & antenna, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ ) {
        if ( _antenna[ chan ] != antenna ) {
          _antenna[ chan ] = antenna;
          return dev->set_antenna( antenna, dev_chan );
        } else { return _antenna[ chan ]; }
      }

  return "";
}

std::string source_impl::get_antenna( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_antenna( dev_chan );

  return "";
}

void source_impl::set_dc_offset_mode( int mode, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        dev->set_dc_offset_mode( mode, dev_chan );
}

void source_impl::set_dc_offset( const std::complex<double> &offset, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        dev->set_dc_offset( offset, dev_chan );
}

void source_impl::set_iq_balance_mode( int mode, size_t chan )
{
  size_t channel = 0;
#ifdef HAVE_IQBALANCE
  BOOST_FOREACH( source_iface *dev, _devs ) {
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++) {
      if ( chan == channel++ ) {
        if ( chan < _iq_opt.size() && chan < _iq_fix.size() ) {
          gr::iqbalance::optimize_c *opt = _iq_opt[chan];
          gr::iqbalance::fix_cc *fix = _iq_fix[chan];

          if ( IQBalanceOff == mode  ) {
            opt->set_period( 0 );
            /* store current values in order to be able to restore them later */
            _vals[ chan ] = std::pair< float, float >( fix->mag(), fix->phase() );
            fix->set_mag( 0.0f );
            fix->set_phase( 0.0f );
          } else if ( IQBalanceManual == mode ) {
            if ( opt->period() == 0 ) { /* transition from Off to Manual */
              /* restore previous values */
              std::pair< float, float > val = _vals[ chan ];
              fix->set_mag( val.first );
              fix->set_phase( val.second );
            }
            opt->set_period( 0 );
          } else if ( IQBalanceAutomatic == mode ) {
            opt->set_period( dev->get_sample_rate() / 5 );
            opt->reset();
          }
        }
      }
    }
  }
#else
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->set_iq_balance_mode( mode, dev_chan );
#endif
}

void source_impl::set_iq_balance( const std::complex<double> &balance, size_t chan )
{
  size_t channel = 0;
#ifdef HAVE_IQBALANCE
  BOOST_FOREACH( source_iface *dev, _devs ) {
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++) {
      if ( chan == channel++ ) {
        if ( chan < _iq_opt.size() && chan < _iq_fix.size() ) {
          gr::iqbalance::optimize_c *opt = _iq_opt[chan];
          gr::iqbalance::fix_cc *fix = _iq_fix[chan];

          if ( opt->period() == 0 ) { /* automatic optimization desabled */
            fix->set_mag( balance.real() );
            fix->set_phase( balance.imag() );
          }
        }
      }
    }
  }
#else
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->set_iq_balance( balance, dev_chan );
#endif
}

double source_impl::set_bandwidth( double bandwidth, size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ ) {
        if ( _bandwidth[ chan ] != bandwidth || 0.0f == bandwidth ) {
          _bandwidth[ chan ] = bandwidth;
          return dev->set_bandwidth( bandwidth, dev_chan );
        } else { return _bandwidth[ chan ]; }
      }

  return 0;
}

double source_impl::get_bandwidth( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_bandwidth( dev_chan );

  return 0;
}

osmosdr::freq_range_t source_impl::get_bandwidth_range( size_t chan )
{
  size_t channel = 0;
  BOOST_FOREACH( source_iface *dev, _devs )
    for (size_t dev_chan = 0; dev_chan < dev->get_num_channels(); dev_chan++)
      if ( chan == channel++ )
        return dev->get_bandwidth_range( dev_chan );

  return osmosdr::freq_range_t();
}

void source_impl::set_time_source(const std::string &source, const size_t mboard)
{
  if (mboard != osmosdr::ALL_MBOARDS){
      _devs.at(mboard)->set_time_source( source );
      return;
  }

  for (size_t m = 0; m < _devs.size(); m++){ /* propagate ALL_MBOARDS */
      _devs.at(m)->set_time_source( source, osmosdr::ALL_MBOARDS );
  }
}

std::string source_impl::get_time_source(const size_t mboard)
{
  return _devs.at(mboard)->get_time_source( mboard );
}

std::vector<std::string> source_impl::get_time_sources(const size_t mboard)
{
  return _devs.at(mboard)->get_time_sources( mboard );
}

void source_impl::set_clock_source(const std::string &source, const size_t mboard)
{
  if (mboard != osmosdr::ALL_MBOARDS){
      _devs.at(mboard)->set_clock_source( source );
      return;
  }

  for (size_t m = 0; m < _devs.size(); m++){ /* propagate ALL_MBOARDS */
      _devs.at(m)->set_clock_source( source, osmosdr::ALL_MBOARDS );
  }
}

std::string source_impl::get_clock_source(const size_t mboard)
{
  return _devs.at(mboard)->get_clock_source( mboard );
}

std::vector<std::string> source_impl::get_clock_sources(const size_t mboard)
{
  return _devs.at(mboard)->get_clock_sources( mboard );
}

double source_impl::get_clock_rate(size_t mboard)
{
  return _devs.at(mboard)->get_clock_rate( mboard );
}

void source_impl::set_clock_rate(double rate, size_t mboard)
{
  if (mboard != osmosdr::ALL_MBOARDS){
      _devs.at(mboard)->set_clock_rate( rate );
      return;
  }

  for (size_t m = 0; m < _devs.size(); m++){ /* propagate ALL_MBOARDS */
      _devs.at(m)->set_clock_rate( rate, osmosdr::ALL_MBOARDS );
  }
}

osmosdr::time_spec_t source_impl::get_time_now(size_t mboard)
{
  return _devs.at(mboard)->get_time_now( mboard );
}

osmosdr::time_spec_t source_impl::get_time_last_pps(size_t mboard)
{
  return _devs.at(mboard)->get_time_last_pps( mboard );
}

void source_impl::set_time_now(const osmosdr::time_spec_t &time_spec, size_t mboard)
{
  if (mboard != osmosdr::ALL_MBOARDS){
      _devs.at(mboard)->set_time_now( time_spec );
      return;
  }

  for (size_t m = 0; m < _devs.size(); m++){ /* propagate ALL_MBOARDS */
      _devs.at(m)->set_time_now( time_spec, osmosdr::ALL_MBOARDS );
  }
}

void source_impl::set_time_next_pps(const osmosdr::time_spec_t &time_spec)
{
  BOOST_FOREACH( source_iface *dev, _devs )
  {
    dev->set_time_next_pps( time_spec );
  }
}

void source_impl::set_time_unknown_pps(const osmosdr::time_spec_t &time_spec)
{
  BOOST_FOREACH( source_iface *dev, _devs )
  {
    dev->set_time_unknown_pps( time_spec );
  }
}
