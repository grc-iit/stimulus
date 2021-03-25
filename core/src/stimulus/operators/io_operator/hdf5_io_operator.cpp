#include <stimulus/operators/io_operator/hdf5_io_operator.h>

Data HDF5IOOperator::execute() {
  hid_t file = H5Fopen(dataset_.name_.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t dataset = H5Dopen(file, dataset_.field_name.c_str(), H5P_DEFAULT);

  hid_t dataspace = H5Dget_space(dataset); /* dataspace handle */
  int rank = H5Sget_simple_extent_ndims(dataspace);
  hsize_t dimsm[rank], dims_out[rank];
  int status_n = H5Sget_simple_extent_dims(dataspace, dims_out, NULL);
  hid_t datatype = H5Dget_type(dataset);
  size_t element_size = H5Tget_size(datatype) * rank;
  size_t elements_per_dim = 1;
  for (int i = 1; i < rank; ++i) {
    elements_per_dim *= dims_out[i];
  }
  size_t num_elements = transfer_size_ / (element_size * elements_per_dim);
  size_t start = element_index_ * num_elements;

  hsize_t count[rank], count_out[rank];
  hsize_t offset[rank], offset_out[rank];
  for (int i = 0; i < rank; ++i) {
    count[i] = dims_out[i];
    offset[i] = 0;
    offset_out[i] = 0;
    count_out[i] = dims_out[i];
  }
  offset[0] = start;
  count[0] = num_elements;
  int status =
      H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, offset, NULL, count, NULL);

  /*
   * Define the memory dataspace.
   */
  dimsm[0] = num_elements;
  hid_t memspace = H5Screate_simple(rank, dimsm, NULL);

  /*
   * Define memory hyperslab.
   */
  count_out[0] = num_elements;
  status = H5Sselect_hyperslab(memspace, H5S_SELECT_SET, offset_out, NULL,
                               count_out, NULL);

  /*
   * Read data from hyperslab in the file into the hyperslab in
   * memory and display.
   */
  size_t num_elements_total = 1;
  for (int i = 0; i < rank; ++i) {
    num_elements_total *= count_out[i];
  }
  void* data_out = malloc(num_elements_total * element_size);
  status = H5Dread(dataset, H5T_NATIVE_INT, memspace, dataspace, H5P_DEFAULT,
                   data_out);
  H5Dclose(dataset);
  H5Sclose(dataspace);
  H5Sclose(memspace);
  H5Fclose(file);
  Data return_data;
  return_data.buffer_ = data_out;
  return_data.size_ = num_elements_total * element_size;
  return return_data;
}
